#ifndef INDIVIDUALPLATFORMER_COMPONENTS_H

#include <string>
#include <SFML/Graphics.hpp>
#include <unordered_map>
#include <memory>
#include <iostream>

#define INDIVIDUALPLATFORMER_COMPONENTS_H

using namespace std;

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
        shape.setFillColor(color);
    }

    explicit Renderable(sf::Vector2f size, const std::string& texturePath) {
        shape.setSize(size);

        texture = std::make_shared<sf::Texture>();
        if (!texture->loadFromFile(texturePath)) {
            shape.setFillColor(sf::Color::Magenta);
        } else {
            shape.setTexture(texture.get());
        }
    }
};

struct PlayerTag {};

struct WallTag {};

struct SpringTag {};

struct SpikeTag {};

struct GoalTag {};

struct ProjectileTag {};

struct TargetTag {};
#endif //INDIVIDUALPLATFORMER_COMPONENTS_H
