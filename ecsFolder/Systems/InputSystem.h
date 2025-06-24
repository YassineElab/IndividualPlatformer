#ifndef INDIVIDUALPLATFORMER_INPUTSYSTEM_H

#include "../System/Types.h"
#include "../System/System.h"
#include "../Components/Components.h"

#define INDIVIDUALPLATFORMER_INPUTSYSTEM_H

class World;

class InputSystem : public System {
public:
    void update(World& world);

    void AddEntity(Entity entity, World& world);
};

#endif //INDIVIDUALPLATFORMER_INPUTSYSTEM_H
