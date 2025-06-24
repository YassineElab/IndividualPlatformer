#include "ConcreteFactory.h"
#include "../World/World.h"

ConcreteFactory::ConcreteFactory(sf::RenderWindow& window) : window(window) {}

Entity ConcreteFactory::createPlayer(World& world, float x, float y, float width, float height) {
    Entity player = world.createEntity();

    world.positions[player] = Position{x, y};
    world.gravities[player] = Gravity{};
    world.sizes[player] = Size{width, height};
    world.velocities[player] = Velocity{0.f, 0.f};
    world.renderables[player] = Renderable{{width, height}, "ecsFolder/Resources/Pics/player.png"};
    world.movementInputs[player] = MovementInput{};
    world.jumps[player] = Jump{};
    world.transforms[player] = Transform{.position = {x, y}};
    world.colliders[player] = Collider{
            .bounds = {x, y, width, height},
            .isStatic = false
    };
    world.playerTags.insert({player, PlayerTag{}});

    return player;
}

Entity ConcreteFactory::createWall(World& world, float x, float y, float width, float height) {
    Entity wall = world.createEntity();

    world.transforms[wall] = Transform{.position = {x, y}};
    world.colliders[wall] = Collider{
            .bounds = {x, y, width, height},
            .isStatic = true
    };
    world.positions[wall] = Position{x, y};
    world.sizes[wall] = Size{width, height};
    world.renderables[wall] = Renderable{{width, height}, "ecsFolder/Resources/Pics/blue.png"};
    world.wallTags.insert({wall, WallTag{}});

    return wall;
}

Entity ConcreteFactory::createSpring(World& world, float x, float y, float width, float height) {
    Entity spring = world.createEntity();

    world.transforms[spring] = Transform{.position = {x, y}};
    world.positions[spring] = Position{x, y};
    world.sizes[spring] = Size{width, height};
    world.renderables[spring] = Renderable{{width, height}, "ecsFolder/Resources/Pics/spring.gif"};
    world.colliders[spring] = Collider{
            .bounds = {x, y, width, height},
            .isStatic = true
    };
    world.springTags.insert({spring, SpringTag{}});

    return spring;
}

Entity ConcreteFactory::createSpike(World &world, float x, float y, float width, float height) {
    Entity spike = world.createEntity();

    world.transforms[spike] = Transform{.position = {x, y}};
    world.positions[spike] = Position{x, y};
    world.sizes[spike] = Size{width, height};
    world.renderables[spike] = Renderable{{width, height}, "ecsFolder/Resources/Pics/spike.png"};
    world.colliders[spike] = Collider{
            .bounds = {x, y, width, height},
            .isStatic = true
    };
    world.spikeTags.insert({spike, SpikeTag{}});

    return spike;
}

Entity ConcreteFactory::createGoal(World &world, float x, float y, float width, float height) {
    Entity goal = world.createEntity();

    world.transforms[goal] = Transform{.position = {x, y}};
    world.positions[goal] = Position{x, y};
    world.sizes[goal] = Size{width, height};
    world.renderables[goal] = Renderable{{width, height}, "ecsFolder/Resources/Pics/goal.jpg"};
    world.colliders[goal] = Collider{
            .bounds = {x, y, width, height},
            .isStatic = true
    };
    world.goalTags.insert({goal, GoalTag{}});

    return goal;
}

Entity ConcreteFactory::createProjectile(World &world, float x, float y, float width, float height) {
    Entity projectile = world.createEntity();

    world.transforms[projectile] = Transform{.position = {x, y}};
    world.positions[projectile] = Position{x, y};
    world.sizes[projectile] = Size{width, height};
    world.renderables[projectile] = Renderable{{width, height}, sf::Color::Magenta};
    world.colliders[projectile] = Collider{
            .bounds = {x, y, width, height},
            .isStatic = true
    };
    world.projectileTags.insert({projectile, ProjectileTag{}});

    return projectile;
}

Entity ConcreteFactory::createTarget(World &world, float x, float y, float width, float height) {
    Entity target = world.createEntity();

    world.transforms[target] = Transform{.position = {x, y}};
    world.positions[target] = Position{x, y};
    world.sizes[target] = Size{width, height};
    world.renderables[target] = Renderable{{width, height}, "ecsFolder/Resources/Pics/target.png"};
    world.colliders[target] = Collider{
            .bounds = {x, y, width, height},
            .isStatic = true
    };
    world.targets[target] = {
            .isHit = false
    };
    world.targetTags.insert({target, TargetTag{}});

    return target;
}
