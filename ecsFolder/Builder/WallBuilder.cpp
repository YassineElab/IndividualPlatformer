#include "WallBuilder.h"
#include "../Factories/AbstractFactory.h"
#include "../World/World.h"

WallBuilder::WallBuilder(World& world, AbstractFactory& factory)
        : world(world), factory(factory) {}

WallBuilder& WallBuilder::makeWall(float x, float y, float width, float height) {
    entity = factory.createWall(world, x, y, width, height);
    return *this;
}

Entity WallBuilder::build() {
    return entity;
}
