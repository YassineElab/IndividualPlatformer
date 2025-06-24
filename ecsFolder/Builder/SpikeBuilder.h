#ifndef INDIVIDUALPLATFORMER_SPIKEBUILDER_H

#include "../System/Types.h"

#define INDIVIDUALPLATFORMER_SPIKEBUILDER_H

class World;
class AbstractFactory;

class SpikeBuilder {
private:
    World& world;
    AbstractFactory& factory;
    Entity entity;

public:
    SpikeBuilder(World& world, AbstractFactory& factory);

    SpikeBuilder& makeSpike(float x, float y, float width, float height);

    Entity build();
};



#endif //INDIVIDUALPLATFORMER_SPIKEBUILDER_H
