#include "ProjectileSystem.h"
#include "../World/World.h"

void ProjectileSystem::update(World& world, float deltaTime) {
    for (auto entity: entities) {
        if (!world.positions.contains(entity) ||
            !world.velocities.contains(entity))
            continue;

        auto& position = world.positions[entity];
        auto& velocity = world.velocities[entity];

        position.x += velocity.dx * deltaTime;
        position.y += velocity.dy * deltaTime;
    }
}

void ProjectileSystem::AddEntity(Entity entity, World &world) {
    if (world.positions.contains(entity) &&
        world.projectiles.contains(entity) &&
        world.velocities.contains(entity)) {
        entities.insert(entity);
    }
}