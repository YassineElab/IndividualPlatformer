#ifndef INDIVIDUALPLATFORMER_PROJECTILEBUILDER_H

#include "../System/Types.h"

#define INDIVIDUALPLATFORMER_PROJECTILEBUILDER_H


class World;
class AbstractFactory;

class ProjectileBuilder {
private:
    World& world;
    AbstractFactory& factory;
    Entity entity;

public:
    ProjectileBuilder(World& world, AbstractFactory& factory);

    ProjectileBuilder& makeProjectile(float x, float y, float width, float height);

    Entity build();
};

#endif //INDIVIDUALPLATFORMER_PROJECTILEBUILDER_H
