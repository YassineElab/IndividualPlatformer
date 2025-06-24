#ifndef INDIVIDUALPLATFORMER_PHYSICSSYSTEM_H

#include "../System/Types.h"
#include "../System/System.h"
#include "../Components/Components.h"

#define INDIVIDUALPLATFORMER_PHYSICSSYSTEM_H

class World;

class PhysicsSystem : public System {
public:
    void update(World& world, float movementMul);

    void AddEntity(Entity entity, World& world);
};

#endif //INDIVIDUALPLATFORMER_PHYSICSSYSTEM_H
