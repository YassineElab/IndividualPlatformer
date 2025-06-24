#include "SpikeBuilder.h"
#include "../Factories/AbstractFactory.h"
#include "../World/World.h"

SpikeBuilder::SpikeBuilder(World& world, AbstractFactory& factory)
        : world(world), factory(factory) {}

SpikeBuilder& SpikeBuilder::makeSpike(float x, float y, float width, float height) {
    entity = factory.createSpike(world, x, y, width, height);
    return *this;
}

Entity SpikeBuilder::build() {
    return entity;
}
