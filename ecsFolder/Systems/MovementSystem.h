#ifndef INDIVIDUALPLATFORMER_MOVEMENTSYSTEM_H

#include "../System/Types.h"
#include "../System/System.h"
#include "../Components/Components.h"

#define INDIVIDUALPLATFORMER_MOVEMENTSYSTEM_H

class World;

class MovementSystem : public System {
public:
    void update(World& world, float deltaTime);

    void AddEntity(Entity entity, World& world);
};

#endif //INDIVIDUALPLATFORMER_MOVEMENTSYSTEM_H
