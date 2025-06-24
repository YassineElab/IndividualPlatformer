#ifndef INDIVIDUALPLATFORMER_TARGETBUILDER_H

#include "../System/Types.h"

#define INDIVIDUALPLATFORMER_TARGETBUILDER_H

class World;
class AbstractFactory;

class TargetBuilder {
private:
    World& world;
    AbstractFactory& factory;
    Entity entity;

public:
    TargetBuilder(World& world, AbstractFactory& factory);

    TargetBuilder& makeTarget(float x, float y, float width, float height);

    Entity build();
};


#endif //INDIVIDUALPLATFORMER_TARGETBUILDER_H
