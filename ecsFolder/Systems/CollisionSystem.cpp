#include "CollisionSystem.h"
#include "../World/World.h"
#include <vector>
#include "../Game/EnemyState.h"

using std::vector;

void CollisionSystem::AddEntity(Entity entity, World& world) {
    if (world.positions.contains(entity) && world.colliders.contains(entity)) {
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

        collider.bounds = { position.x, position.y, size.width, size.height };
        if (world.enemyTags.contains(entity)) {
            collider.bounds.top;
        }
        quadtree.insert(entity, collider.bounds);
    }

    vector<Entity> projectilesToRemove;

    for (auto& [entity, projectile] : world.projectiles) {
        if (std::find(projectilesToRemove.begin(), projectilesToRemove.end(), entity) != projectilesToRemove.end())
            continue;

        if (!world.positions.contains(entity) || !world.colliders.contains(entity)) continue;

        auto& pos = world.positions[entity];
        auto& sz  = world.sizes[entity];
        sf::FloatRect curr(pos.x, pos.y, sz.width, sz.height);

        float dx = 0.f, dy = 0.f;
        if (world.velocities.contains(entity)) {
            const auto& vv = world.velocities[entity];
            dx = vv.dx * world.frameDt;
            dy = vv.dy * world.frameDt;
        }

        sf::FloatRect prev(curr.left - dx, curr.top - dy, curr.width, curr.height);

        const float left   = min(curr.left, prev.left);
        const float top    = min(curr.top,  prev.top);
        const float right  = max(curr.left + curr.width,  prev.left + prev.width);
        const float bottom = max(curr.top  + curr.height, prev.top  + prev.height);
        sf::FloatRect swept(left, top, right - left, bottom - top);

        auto possibleCollisions = quadtree.retrieve(swept);

        for (const auto& [otherEntity, otherBounds] : possibleCollisions) {
            if (entity == otherEntity) continue;
            if (!world.colliders.contains(otherEntity)) continue;

            const auto& otherCollider = world.colliders[otherEntity];

            if (world.targetTags.contains(otherEntity)) {
                auto& target = world.targets[otherEntity];
                if ((curr.intersects(otherBounds) || swept.intersects(otherBounds)) && !target.isHit) {
                    target.isHit = true;
                    world.hitTargets.push_back(target);
                    projectilesToRemove.push_back(entity);
                    world.destroyEntity(entity);
                    world.destroyEntity(otherEntity);
                    break;
                }
            }

            if (world.enemyTags.contains(otherEntity)) {
                if (curr.intersects(otherBounds) || swept.intersects(otherBounds)) {
                    projectilesToRemove.push_back(entity);

                    auto& enemy = world.enemies[otherEntity];
                    const sf::Vector2f rp = enemy.respawnPos;

                    world.positions[otherEntity] = Position{rp.x, rp.y};
                    if (world.transforms.contains(otherEntity))
                        world.transforms[otherEntity].position = rp;
                    if (world.colliders.contains(otherEntity)) {
                        world.colliders[otherEntity].bounds.left = rp.x;
                        world.colliders[otherEntity].bounds.top  = rp.y;
                    }
                    if (world.velocities.contains(otherEntity)) {
                        world.velocities[otherEntity].dx = 0.f;
                        world.velocities[otherEntity].dy = 0.f;
                    }

                    enemy.goingToB = true;
                    enemy.timeSinceSeen = 0.f;
                    enemy.cooldownLeft  = 0.f;
                    enemy.dashLeft      = 0.f;
                    enemy.state = &PatrolState::instance();
                    break;
                }
            }

            if (otherCollider.isStatic) {
                auto& ppos = world.positions[entity];
                sf::FloatRect pb(ppos.x, ppos.y, sz.width, sz.height);
                if (resolveProjectileCollision(ppos, pb, otherBounds)) {
                    projectilesToRemove.push_back(entity);
                    break;
                }
            }
        }
    }

    for (auto e : projectilesToRemove) {
        world.destroyEntity(e);
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

            if (world.enemyTags.contains(otherEntity)) {
                if (playerBounds.intersects(otherBounds)) {
                    auto& enemy = world.enemies[otherEntity];
                    const sf::Vector2f rp = enemy.respawnPos;

                    if (world.positions.contains(otherEntity))
                        world.positions[otherEntity] = Position{rp.x, rp.y};
                    if (world.transforms.contains(otherEntity))
                        world.transforms[otherEntity].position = rp;
                    if (world.colliders.contains(otherEntity)) {
                        world.colliders[otherEntity].bounds.left = rp.x;
                        world.colliders[otherEntity].bounds.top  = rp.y;
                    }
                    if (world.velocities.contains(otherEntity)) {
                        world.velocities[otherEntity].dx = 0.f;
                        world.velocities[otherEntity].dy = 0.f;
                    }

                    enemy.goingToB = true;
                    enemy.timeSinceSeen = 0.f;
                    enemy.cooldownLeft  = 0.f;
                    enemy.dashLeft      = 0.f;
                    enemy.state = &PatrolState::instance();

                    auto itHp = world.healths.find(entity.first);
                    if (itHp != world.healths.end()) {
                        auto& hp = itHp->second.hp;
                        if (hp > 0) {
                            --hp;
                            if (hp <= 0) {
                                world.restartRequested = true;
                            }
                        }
                    }
                }
                continue;
            }

            const auto& otherCollider = world.colliders[otherEntity];

            if (world.spikeTags.contains(otherEntity)) {
                if (resolveSpikeCollision(playerBounds, otherBounds)) {
                    position.x = 50.f;
                    position.y = -60.f;
                    velocity.dx = 0; velocity.dy = 0;
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
                if (bounced) grounded = false;
                continue;
            }

            if (world.goalTags.contains(otherEntity)) {
                if (playerBounds.intersects(otherBounds)) {
                    if (world.hitTargets.size() == 3) {
                        world.setNextLevel(true);
                        continue;
                    }
                }
            }

            if (!otherCollider.isStatic) continue;

            bool hitGround = resolveWallCollision(position, &velocity, playerBounds, otherBounds, &onLeftWall, &onRightWall);
            playerBounds.left = position.x;
            playerBounds.top = position.y;
            if (hitGround) grounded = true;
        }

        if (world.jumps.contains(entity.first)) {
            world.jumps[entity.first].isGrounded = grounded;
            world.jumps[entity.first].onLeftWall = onLeftWall;
            world.jumps[entity.first].onRightWall = onRightWall;
            if (grounded) world.jumps[entity.first].jumpCount = 0;
        }
    }
}