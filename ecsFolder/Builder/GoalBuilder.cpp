#include "GoalBuilder.h"
#include "../Factories/AbstractFactory.h"
#include "../World/World.h"

GoalBuilder::GoalBuilder(World& world, AbstractFactory& factory)
        : world(world), factory(factory) {}

GoalBuilder& GoalBuilder::makeGoal(float x, float y, float width, float height) {
    entity = factory.createGoal(world, x, y, width, height);
    return *this;
}

Entity GoalBuilder::build() {
    return entity;
}