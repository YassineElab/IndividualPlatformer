#ifndef INDIVIDUALPLATFORMER_COMPONENTS_H

#include <string>
#include <SFML/Graphics.hpp>
#include <unordered_map>
#include <memory>
#include <iostream>

#define INDIVIDUALPLATFORMER_COMPONENTS_H

using namespace std;

class EnemyState;

struct Enemy {
    EnemyState* state = nullptr;
    sf::Vector2f anchorA{0.f,0.f};
    sf::Vector2f anchorB{0.f,0.f};
    sf::Vector2f respawnPos{0.f,0.f};

    bool  goingToB = true;
    float seeRadius = 260.f;
    float attackRange = 60.f;
    float loseSightTime = 1.f;
    float timeSinceSeen = 0.f;
    float maxSpeed = 180.f;
    float accel = 520.f;
    float dashSpeed = 340.f;
    float dashTime = 0.18f;
    float dashLeft = 0.f;
    float attackCooldown = 0.8f;
    float cooldownLeft = 0.f;

    bool respawnRequested = false;
};

struct Collider {
    sf::FloatRect bounds;
    bool isStatic = false;
};

struct Transform {
    sf::Vector2f position;
};

struct Gravity {
    float force = 0.2f;
};

struct Jump {
    float impulse = 4.f;
    bool isGrounded = false;
    bool onLeftWall = false;
    bool onRightWall = false;
    float wallJumpStrength = 5.f;
    float wallJumpHorizontalPush = 7.f;
    float wallJumpControlLockTime = 9.f;
    float wallJumpControlTimer = 0.f;
    int jumpCount = 0;
    bool jumpPrev = false;

    int frame1 = 0;
    int frame1Window = 8;
    int frame2 = 0;
    int frame2Window = 8;
    int maxAirJumps = 1;
};

struct Spring {
    float bounceImpulse = 7.f;
};

struct Spike {
};

struct Projectile {
    float lifeTime = 400.0f;
    float timeAlive = 0.0f;
};

struct Shooting {
    float shootCooldown = 5.f;
    float timeSinceLastShot = 0;
    float projectileLifetime = 15.0f;
    float projectileSpeed = 10.0f;
};

struct Target {
    bool isHit = false;
};

struct MovementInput {
    bool right = false;
    bool left = false;
    bool jump = false;
    bool leftShot = false;
    bool rightShot = false;
};

struct Position {
    float x;
    float y;
};

struct Size {
    float width;
    float height;
};

struct Velocity {
    float dx = 0;
    float dy = 0;
    float maxSpeed = 3.f;
    float acceleration = 300.f;
    float deceleration = 4.f;
};

struct Renderable {
    sf::RectangleShape shape;
    std::shared_ptr<sf::Texture> texture;

    Renderable() = default;

    explicit Renderable(sf::Vector2f size, sf::Color color = sf::Color::White) {
        shape.setSize(size);
        shape.setOrigin(0.f, size.y);
        shape.setFillColor(color);
    }

    explicit Renderable(sf::Vector2f size, const std::string& texturePath) {
        shape.setSize(size);
        shape.setOrigin(0.f, size.y);

        texture = std::make_shared<sf::Texture>();
        if (!texture->loadFromFile(texturePath)) {
            shape.setFillColor(sf::Color::Magenta);
        } else {
            shape.setTexture(texture.get());
            shape.setScale(1.f, -1.f);
        }
    }
};

struct EnemyTag {};

struct Health { int hp = 1; };

struct PlayerTag {};

struct WallTag {};

struct SpringTag {};

struct SpikeTag {};

struct GoalTag {};

struct ProjectileTag {};

struct TargetTag {};
#endif //INDIVIDUALPLATFORMER_COMPONENTS_H
