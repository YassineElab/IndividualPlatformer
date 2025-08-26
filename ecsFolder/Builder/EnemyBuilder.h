#ifndef INDIVIDUALPLATFORMER_ENEMYBUILDER_H

#include "../System/Types.h"
#include <SFML/Graphics.hpp>

#define INDIVIDUALPLATFORMER_ENEMYBUILDER_H

class World;
class AbstractFactory;

class EnemyBuilder {
private:
    World& world;
    AbstractFactory& factory;
    Entity entity;

public:
    EnemyBuilder(World& world, AbstractFactory& factory);

    EnemyBuilder& makeEnemy(float x, float y, float width, float height, sf::Vector2f A, sf::Vector2f B);

    Entity build();
};


#endif //INDIVIDUALPLATFORMER_ENEMYBUILDER_H
