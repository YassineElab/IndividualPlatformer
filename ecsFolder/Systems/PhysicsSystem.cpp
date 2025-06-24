#include "PhysicsSystem.h"
#include "../World/World.h"

void PhysicsSystem::update(World& world, float movementMul) {
    for (auto entity : entities) {
        if (!world.velocities.contains(entity) ||
            !world.gravities.contains(entity)) {
            continue;
        }

        auto& velocity = world.velocities[entity];
        auto& gravity = world.gravities[entity];
        bool isGrounded = world.jumps.contains(entity) ? world.jumps[entity].isGrounded : false;

        if (!isGrounded) {
            velocity.dy -= gravity.force * movementMul;
        }
    }
}

void PhysicsSystem::AddEntity(Entity entity, World& world) {
    if (world.velocities.contains(entity) &&
        world.gravities.contains(entity) &&
        world.jumps.contains(entity)) {
        entities.insert(entity);
    }
}