#include "JumpSystem.h"
#include "../World/World.h"

void JumpSystem::update(World& world) {
    for (auto entity : entities) {
        if (!world.movementInputs.contains(entity) ||
            !world.velocities.contains(entity)     ||
            !world.jumps.contains(entity)) {
            continue;
        }

        auto& input    = world.movementInputs[entity];
        auto& velocity = world.velocities[entity];
        auto& jump     = world.jumps[entity];

        bool pressedEdge = (input.jump && !jump.jumpPrev);
        jump.jumpPrev = input.jump;

        if (pressedEdge) {
            jump.frame1 = jump.frame1Window;
        } else if (jump.frame1 > 0) {
            jump.frame1--;
        }

        if (jump.isGrounded) {
            jump.frame2 = jump.frame2Window;
        } else if (jump.frame2 > 0) {
            jump.frame2--;
        }

        bool wantJump   = (jump.frame1 > 0);
        bool canPrimary = (jump.isGrounded || jump.frame2 > 0);
        bool canAir     = (!jump.isGrounded && jump.jumpCount == 1 && jump.maxAirJumps >= 1);

        if (wantJump) {
            if (jump.onLeftWall) {
                velocity.dx = jump.wallJumpHorizontalPush;
                velocity.dy = jump.wallJumpStrength;
                jump.jumpCount = 2;
                jump.onLeftWall = false;
                jump.wallJumpControlTimer = jump.wallJumpControlLockTime;
                jump.isGrounded = false;
                jump.frame1 = 0;
                jump.frame2 = 0;
            }
            else if (jump.onRightWall) {
                velocity.dx = -jump.wallJumpHorizontalPush;
                velocity.dy = jump.wallJumpStrength;
                jump.jumpCount = 2;
                jump.onRightWall = false;
                jump.wallJumpControlTimer = jump.wallJumpControlLockTime;
                jump.isGrounded = false;
                jump.frame1 = 0;
                jump.frame2 = 0;
            }
            else if (canPrimary) {
                velocity.dy = jump.impulse;
                jump.isGrounded = false;
                jump.jumpCount  = 1;
                jump.frame1 = 0;
                jump.frame2 = 0;
            }
            else if (canAir) {
                velocity.dy = jump.impulse;
                jump.jumpCount  = 2;
                jump.frame1 = 0;
            }
        }

        if (jump.isGrounded) {
            jump.jumpCount = 0;
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