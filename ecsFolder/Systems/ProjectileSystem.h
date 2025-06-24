#ifndef INDIVIDUALPLATFORMER_PROJECTILESYSTEM_H

#include "../System/Types.h"
#include "../System/System.h"
#include "../Components/Components.h"

#define INDIVIDUALPLATFORMER_PROJECTILESYSTEM_H

class World;

class ProjectileSystem: public System {
public:
    void update(World& world, float deltaTime);

    void AddEntity(Entity entity, World& world);
};


#endif //INDIVIDUALPLATFORMER_PROJECTILESYSTEM_H
