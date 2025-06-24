#include "MovementSystem.h"
#include "../World/World.h"

void MovementSystem::update(World& world, float movementMul) {
    for (auto entity : entities) {
        if (!world.velocities.contains(entity) ||
            !world.positions.contains(entity) ||
            !world.movementInputs.contains(entity) ||
            !world.jumps.contains(entity)) {
            continue;
        }

        auto& velocity = world.velocities[entity];
        auto& position = world.positions[entity];
        auto& input = world.movementInputs[entity];
        auto& jump = world.jumps[entity];

        if (jump.wallJumpControlTimer > 0.f) {
            jump.wallJumpControlTimer -= movementMul;
        }

        if (jump.wallJumpControlTimer <= 0.f) {
            if (input.right) {
                velocity.dx = min(velocity.maxSpeed, velocity.dx + velocity.acceleration * movementMul);
            } else if (input.left) {
                velocity.dx = max(-velocity.maxSpeed, velocity.dx - velocity.acceleration * movementMul);
            } else {
                if (velocity.dx > 0) {
                    velocity.dx = max(0.f, velocity.dx - velocity.deceleration * movementMul);
                } else if (velocity.dx < 0) {
                    velocity.dx = min(0.f, velocity.dx + velocity.deceleration * movementMul);
                }
            }
        }
        position.x += velocity.dx * movementMul;
        position.y += velocity.dy * movementMul;
    }
}

void MovementSystem::AddEntity(Entity entity, World& world) {
    if (world.positions.contains(entity) &&
        world.velocities.contains(entity) &&
        world.movementInputs.contains(entity) &&
        world.colliders.contains(entity)) {
        entities.insert(entity);
    }
}
