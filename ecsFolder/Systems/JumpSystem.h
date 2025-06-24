#ifndef INDIVIDUALPLATFORMER_JUMPSYSTEM_H

#include "../System/Types.h"
#include "../System/System.h"
#include "../Components/Components.h"


#define INDIVIDUALPLATFORMER_JUMPSYSTEM_H

class World;

class JumpSystem: public System {
public:
    void update(World& world);
    void AddEntity(Entity entity, World& world);
};


#endif //INDIVIDUALPLATFORMER_JUMPSYSTEM_H
