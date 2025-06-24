#include "PlayerBuilder.h"
#include "../Factories/AbstractFactory.h"
#include "../World/World.h"

PlayerBuilder::PlayerBuilder(World& world, AbstractFactory& factory)
        : world(world), factory(factory) {}

PlayerBuilder& PlayerBuilder::makePlayer(float x, float y, float width, float height) {
    entity = factory.createPlayer(world, x, y, width, height);
    return *this;
}

Entity PlayerBuilder::build() {
    return entity;
}

