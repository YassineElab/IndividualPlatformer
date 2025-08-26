#include "MovementSystem.h"
#include "../World/World.h"

void MovementSystem::update(World& world, float movementMul) {
    for (auto entity : entities) {
        if (!world.velocities.contains(entity) || !world.positions.contains(entity))
            continue;

        if (world.movementInputs.contains(entity) && world.jumps.contains(entity)) {
            auto& velocity = world.velocities[entity];
            auto& input = world.movementInputs[entity];
            auto& jump = world.jumps[entity];

            if (jump.wallJumpControlTimer > 0.f)
                jump.wallJumpControlTimer -= movementMul;

            if (jump.wallJumpControlTimer <= 0.f) {
                if (input.right) {
                    velocity.dx = min(velocity.maxSpeed, velocity.dx + velocity.acceleration * movementMul);
                } else if (input.left) {
                    velocity.dx = max(-velocity.maxSpeed, velocity.dx - velocity.acceleration * movementMul);
                } else {
                    if (velocity.dx > 0.f)
                        velocity.dx = max(0.f, velocity.dx - velocity.deceleration * movementMul);
                    else if (velocity.dx < 0.f)
                        velocity.dx = min(0.f, velocity.dx + velocity.deceleration * movementMul);
                }
            }
        }
    }

    for (auto& [e, v] : world.velocities) {
        if (!world.positions.contains(e)) continue;

        auto& p = world.positions[e];
        p.x += v.dx * movementMul;
        p.y += v.dy * movementMul;

        if (world.transforms.contains(e))
            world.transforms[e].position = {p.x, p.y};

        if (world.colliders.contains(e)) {
            world.colliders[e].bounds.left = p.x;
            world.colliders[e].bounds.top  = p.y;
        }
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
