#include "CollisionSystem.h"
#include "../World/World.h"

void CollisionSystem::AddEntity(Entity entity, World& world) {
    if (world.positions.contains(entity) &&
        world.colliders.contains(entity)) {
        entities.insert(entity);
    }
}

void CollisionSystem::update(World& world, Quadtree& quadtree) {
    quadtree.clear();

    for (auto entity : entities) {
        if (!world.positions.contains(entity) ||
            !world.colliders.contains(entity) ||
            !world.sizes.contains(entity)) continue;

        auto& position = world.positions[entity];
        auto& collider = world.colliders[entity];
        auto& size = world.sizes[entity];

        collider.bounds = {
                position.x,
                position.y,
                size.width,
                size.height
        };

        quadtree.insert(entity, collider.bounds);
    }

    vector<Entity> projectilesToRemove;
    for (auto& [entity, projectile] : world.projectiles) {
        if (std::find(projectilesToRemove.begin(), projectilesToRemove.end(), entity) != projectilesToRemove.end()) {
            continue;
        }

        if (!world.positions.contains(entity) ||
            !world.colliders.contains(entity)) continue;

        auto& position = world.positions[entity];
        sf::FloatRect projectileBounds(
                position.x,
                position.y,
                world.colliders[entity].bounds.width,
                world.colliders[entity].bounds.height
        );

        auto possibleCollisions = quadtree.retrieve(projectileBounds);

        for (const auto& [otherEntity, otherBounds] : possibleCollisions) {
            if (entity == otherEntity) continue;

            if (world.colliders.contains(otherEntity)) {
                const auto& otherCollider = world.colliders[otherEntity];

                if (world.targetTags.contains(otherEntity)) {
                    auto& target = world.targets[otherEntity];
                    if (projectileBounds.intersects(otherBounds) && !world.targets[otherEntity].isHit){
                        target.isHit = true;
                        world.hitTargets.push_back(target);

                        projectilesToRemove.push_back(entity);

                        world.destroyEntity(entity);
                        world.destroyEntity(otherEntity);
                        break;
                    }
                }

                if (otherCollider.isStatic) {
                    auto& position = world.positions[entity];
                    sf::FloatRect projectileBounds(
                            position.x,
                            position.y,
                            world.colliders[entity].bounds.width,
                            world.colliders[entity].bounds.height
                    );

                    if (resolveProjectileCollision(position, projectileBounds, otherBounds)) {
                        projectilesToRemove.push_back(entity);
                        break;
                    }
                }
            }
        }
    }

    for (auto entity : projectilesToRemove) {
        world.destroyEntity(entity);
    }

    for (auto entity : world.playerTags) {
        if (!world.positions.contains(entity.first) ||
            !world.sizes.contains(entity.first) ||
            !world.colliders.contains(entity.first)) continue;

        auto& position = world.positions[entity.first];
        auto& size = world.sizes[entity.first];
        auto& velocity = world.velocities[entity.first];

        sf::FloatRect playerBounds(position.x, position.y, size.width, size.height);

        auto possibleCollisions = quadtree.retrieve(playerBounds);

        bool grounded = false;

        bool onLeftWall = false;
        bool onRightWall = false;

        for (const auto& [otherEntity, otherBounds] : possibleCollisions) {
            if (entity.first == otherEntity || !world.colliders.contains(otherEntity)) continue;

            const auto& otherCollider = world.colliders[otherEntity];

            if (world.spikeTags.contains(otherEntity)) {
                if (resolveSpikeCollision(playerBounds, otherBounds)) {
                    position.x = 50.f;
                    position.y = -60.f;

                    velocity.dx = 0;
                    velocity.dy = 0;

                    playerBounds.left = position.x;
                    playerBounds.top = position.y;

                    grounded = false;
                    break;
                }
                continue;
            }

            if (world.springTags.contains(otherEntity)) {
                const auto& spring = world.springs[otherEntity];
                bool bounced = resolveSpringCollision(position, &velocity, playerBounds, otherBounds, spring);
                playerBounds.left = position.x;
                playerBounds.top = position.y;
                if (bounced) {
                    grounded = false;
                }
                continue;
            }

            if (world.goalTags.contains(otherEntity)) {
                if (playerBounds.intersects(otherBounds)) {
                    if (world.hitTargets.size() == 3){
                        world.setNextLevel(true);
                        continue;
                    }
                }
            }

            if (!otherCollider.isStatic) continue;

            bool hitGround = resolveWallCollision(position, &velocity, playerBounds, otherBounds, &onLeftWall, &onRightWall);
            playerBounds.left = position.x;
            playerBounds.top = position.y;
            if (hitGround) {
                grounded = true;
            }
        }

        if (world.jumps.contains(entity.first)) {
            world.jumps[entity.first].isGrounded = grounded;
            world.jumps[entity.first].onLeftWall = onLeftWall;
            world.jumps[entity.first].onRightWall = onRightWall;
        }
    }
}
