#include "ShootSystem.h"
#include "../World/World.h"

void ShootSystem::update(World &world, float deltaTime) {
    std::vector<Entity> projectilesToRemove;
    for (auto& [entity, projectile] : world.projectiles) {
        projectile.timeAlive += deltaTime;
        if (projectile.timeAlive >= projectile.lifeTime) {
            projectilesToRemove.push_back(entity);
        }
    }

    for (auto entity : projectilesToRemove) {
        destroyProjectile(world, entity);
    }

    for (auto entity : entities) {
        auto& input = world.movementInputs[entity];
        auto& position = world.positions[entity];
        auto& shooting = world.shooting[entity];

        if (!((input.rightShot || input.leftShot) && shooting.timeSinceLastShot >= shooting.shootCooldown)) {
            shooting.timeSinceLastShot += deltaTime;
        }

        if (input.rightShot && shooting.timeSinceLastShot >= shooting.shootCooldown) {
            shooting.timeSinceLastShot = 0;

            Entity projectile = ProjectileBuilder(world, world.getAbstractFactory())
                    .makeProjectile(position.x + 20.f, position.y + 10.f,
                                    20.f, 5.f)
                    .build();

            world.projectiles[projectile] = {
                    .lifeTime = shooting.projectileLifetime,
                    .timeAlive = 0.0f,
            };

            world.velocities[projectile] = {
                    .dx = 10.f,
                    .dy = 0.f
            };

            if (world.getProjectileSystem()) {
                world.getProjectileSystem()->AddEntity(projectile, world);
            }
        }
        else if (input.leftShot && shooting.timeSinceLastShot >= shooting.shootCooldown) {
            shooting.timeSinceLastShot = 0;

            Entity projectile = ProjectileBuilder(world, world.getAbstractFactory())
                    .makeProjectile(position.x - 20.f, position.y + 10.f,
                                    20.f, 5.f)
                    .build();

            world.projectiles[projectile] = {
                    .lifeTime = shooting.projectileLifetime,
                    .timeAlive = 0.0f,
            };

            world.velocities[projectile] = {
                    .dx = -10.f,
                    .dy = 0.f
            };

            if (world.getProjectileSystem()) {
                world.getProjectileSystem()->AddEntity(projectile, world);
            }
        }
    }
}

void ShootSystem::destroyProjectile(World& world, Entity entity) {
    world.destroyEntity(entity);
}

void ShootSystem::AddEntity(Entity entity, World &world) {
    if (world.movementInputs.contains(entity) &&
        world.positions.contains(entity)) {
        entities.insert(entity);
    }
}
