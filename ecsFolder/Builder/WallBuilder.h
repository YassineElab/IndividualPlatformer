#ifndef INDIVIDUALPLATFORMER_WALLBUILDER_H

#include "../System/Types.h"

#define INDIVIDUALPLATFORMER_WALLBUILDER_H

class World;
class AbstractFactory;

class WallBuilder {
private:
    World& world;
    AbstractFactory& factory;
    Entity entity;

public:
    WallBuilder(World& world, AbstractFactory& factory);

    WallBuilder& makeWall(float x, float y, float width, float height);

    Entity build();
};

#endif //INDIVIDUALPLATFORMER_WALLBUILDER_H
