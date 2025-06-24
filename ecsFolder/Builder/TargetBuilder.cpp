#include "TargetBuilder.h"
#include "../Factories/AbstractFactory.h"
#include "../World/World.h"

TargetBuilder::TargetBuilder(World& world, AbstractFactory& factory)
        : world(world), factory(factory) {}

TargetBuilder& TargetBuilder::makeTarget(float x, float y, float width, float height) {
    entity = factory.createTarget(world, x, y, width, height);
    return *this;
}

Entity TargetBuilder::build() {
    return entity;
}