#include "EnemyBuilder.h"
#include "../Factories/AbstractFactory.h"
#include "../World/World.h"

EnemyBuilder::EnemyBuilder(World& world, AbstractFactory& factory)
        : world(world), factory(factory) {}

EnemyBuilder& EnemyBuilder::makeEnemy(float x, float y, float width, float height, sf::Vector2f A, sf::Vector2f B) {
    entity = factory.createEnemy(world, x, y, width, height, A, B);
    return *this;
}

Entity EnemyBuilder::build() {
    return entity;
}