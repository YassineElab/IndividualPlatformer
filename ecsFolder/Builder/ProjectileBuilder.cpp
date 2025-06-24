#include "ProjectileBuilder.h"
#include "../Factories/AbstractFactory.h"
#include "../World/World.h"

ProjectileBuilder::ProjectileBuilder(World& world, AbstractFactory& factory)
        : world(world), factory(factory) {}

ProjectileBuilder& ProjectileBuilder::makeProjectile(float x, float y, float width, float height) {
    entity = factory.createProjectile(world, x, y, width, height);
    return *this;
}

Entity ProjectileBuilder::build() {
    return entity;
}