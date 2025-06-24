#ifndef INDIVIDUALPLATFORMER_SPRINGBUILDER_H

#include "../System/Types.h"

#define INDIVIDUALPLATFORMER_SPRINGBUILDER_H

class World;
class AbstractFactory;

class SpringBuilder {
private:
    World& world;
    AbstractFactory& factory;
    Entity entity;

public:
    SpringBuilder(World& world, AbstractFactory& factory);

    SpringBuilder& makeSpring(float x, float y, float width, float height);

    Entity build();
};

#endif // INDIVIDUALPLATFORMER_SPRINGBUILDER_H
