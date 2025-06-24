#ifndef INDIVIDUALPLATFORMER_SHOOTSYSTEM_H

#include "../System/Types.h"
#include "../System/System.h"
#include "../Components/Components.h"
#include "../Builder/ProjectileBuilder.h"

#define INDIVIDUALPLATFORMER_SHOOTSYSTEM_H

class World;

class ShootSystem: public System {
private:
    ProjectileBuilder& projectileBuilder;

public:
    explicit ShootSystem(ProjectileBuilder& builder) : projectileBuilder(builder) {}

    void update(World& world, float deltaTime);

    void destroyProjectile(World& world, Entity entity);

    void AddEntity(Entity entity, World& world);
};


#endif //INDIVIDUALPLATFORMER_SHOOTSYSTEM_H
