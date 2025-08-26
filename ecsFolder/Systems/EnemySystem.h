#ifndef INDIVIDUALPLATFORMER_ENEMYSYSTEM_H

#include <unordered_set>
#include <SFML/Graphics.hpp>
#include "../System/Types.h"
#include <cmath>

#define INDIVIDUALPLATFORMER_ENEMYSYSTEM_H

using namespace std;

class World;

class EnemySystem {
public:
    void update(World& world, float dt);
    void AddEntity(Entity e, World& world);
private:
    unordered_set<Entity> entities;
};


#endif //INDIVIDUALPLATFORMER_ENEMYSYSTEM_H
