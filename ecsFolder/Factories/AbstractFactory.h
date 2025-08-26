#ifndef INDIVIDUALPLATFORMER_ABSTRACTFACTORY_H

#include "../System/Types.h"
#include <SFML/Graphics.hpp>

#define INDIVIDUALPLATFORMER_ABSTRACTFACTORY_H

class World;

class AbstractFactory {
public:
    virtual Entity createPlayer(World& world, float x, float y, float width, float height) = 0;
    virtual Entity createWall(World& world, float x, float y, float width, float height) = 0;
    virtual Entity createSpring(World& world, float x, float y, float width, float height) = 0;
    virtual Entity createSpike(World& world, float x, float y, float width, float height) = 0;
    virtual Entity createGoal(World& world, float x, float y, float width, float height) = 0;
    virtual Entity createProjectile(World& world, float x, float y, float width, float height) = 0;
    virtual Entity createTarget(World& world, float x, float y, float width, float height) = 0;
    virtual Entity createEnemy(World& world, float x, float y, float width, float height, sf::Vector2f A, sf::Vector2f B) = 0;
    virtual ~AbstractFactory() = default;
};

#endif //INDIVIDUALPLATFORMER_ABSTRACTFACTORY_H
