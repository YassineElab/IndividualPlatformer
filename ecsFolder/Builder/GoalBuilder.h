#ifndef INDIVIDUALPLATFORMER_GOALBUILDER_H

#include "../System/Types.h"

#define INDIVIDUALPLATFORMER_GOALBUILDER_H


class World;
class AbstractFactory;

class GoalBuilder {
private:
    World& world;
    AbstractFactory& factory;
    Entity entity;

public:
    GoalBuilder(World& world, AbstractFactory& factory);

    GoalBuilder& makeGoal(float x, float y, float width, float height);

    Entity build();
};


#endif //INDIVIDUALPLATFORMER_GOALBUILDER_H
