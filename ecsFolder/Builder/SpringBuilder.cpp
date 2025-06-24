#include "SpringBuilder.h"
#include "../Factories/AbstractFactory.h"
#include "../World/World.h"

SpringBuilder::SpringBuilder(World& world, AbstractFactory& factory)
        : world(world), factory(factory) {}

SpringBuilder& SpringBuilder::makeSpring(float x, float y, float width, float height) {
    entity = factory.createSpring(world, x, y, width, height);
    return *this;
}

Entity SpringBuilder::build() {
    return entity;
}
