#ifndef INDIVIDUALPLATFORMER_PLAYERBUILDER_H

#include "../System/Types.h"

#define INDIVIDUALPLATFORMER_PLAYERBUILDER_H

class World;
class AbstractFactory;

class PlayerBuilder {
private:
    World& world;
    AbstractFactory& factory;
    Entity entity;

public:
    PlayerBuilder(World& world, AbstractFactory& factory);

    PlayerBuilder& makePlayer(float x, float y, float width, float height);

    Entity build();
};

#endif //INDIVIDUALPLATFORMER_PLAYERBUILDER_H