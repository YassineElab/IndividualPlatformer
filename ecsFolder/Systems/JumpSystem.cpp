#include "JumpSystem.h"
#include "../World/World.h"

void JumpSystem::update(World& world) {
    for (auto entity : entities) {
        if (!world.movementInputs.contains(entity) ||
            !world.velocities.contains(entity) ||
            !world.jumps.contains(entity)) {
            continue;
        }

        auto& input = world.movementInputs[entity];
        auto& velocity = world.velocities[entity];
        auto& jump = world.jumps[entity];

        if(input.jump){
            if(jump.onLeftWall){
                velocity.dx = jump.wallJumpHorizontalPush;
                velocity.dy = jump.wallJumpStrength;
                jump.onLeftWall = false;
                jump.wallJumpControlTimer = jump.wallJumpControlLockTime;
            }
            else if (jump.onRightWall) {
                velocity.dx = -jump.wallJumpHorizontalPush;
                velocity.dy = jump.wallJumpStrength;
                jump.onRightWall = false;
                jump.wallJumpControlTimer = jump.wallJumpControlLockTime;
            }
            else if (jump.isGrounded) {
                velocity.dy = jump.impulse;
                jump.isGrounded = false;
            }
        }
    }
}

void JumpSystem::AddEntity(Entity entity, World& world) {
    if (world.movementInputs.contains(entity) &&
        world.velocities.contains(entity) &&
        world.jumps.contains(entity)) {
        entities.insert(entity);
    }
}