#ifndef INDIVIDUALPLATFORMER_CONCRETEFACTORY_H

#include "AbstractFactory.h"
#include "../Components/Components.h"
#include <SFML/Graphics.hpp>

#define INDIVIDUALPLATFORMER_CONCRETEFACTORY_H


class ConcreteFactory : public AbstractFactory {
private:
    sf::RenderWindow& window;

public:
    explicit ConcreteFactory(sf::RenderWindow& window);

    Entity createPlayer(World& world, float x, float y, float width, float height) override;
    Entity createWall(World& world, float x, float y, float width, float height) override;
    Entity createSpring(World& world, float x, float y, float width, float height) override;
    Entity createSpike(World& world, float x, float y, float width, float height) override;
    Entity createGoal(World& world, float x, float y, float width, float height) override;
    Entity createProjectile(World& world, float x, float y, float width, float height) override;
    Entity createTarget(World& world, float x, float y, float width, float height) override;
};

#endif //INDIVIDUALPLATFORMER_CONCRETEFACTORY_H
