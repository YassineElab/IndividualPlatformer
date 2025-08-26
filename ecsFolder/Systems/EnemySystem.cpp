#include "EnemySystem.h"
#include "../World/World.h"
#include "../Game/EnemyState.h"
#include <algorithm>

void EnemySystem::AddEntity(Entity e, World& world) {
    if (world.enemies.contains(e) && world.positions.contains(e) && world.velocities.contains(e))
        entities.insert(e);
}

void EnemySystem::update(World& world, float dt) {
    if (world.playerTags.empty()) return;
    const Entity playerE = world.playerTags.begin()->first;
    auto p = world.positions.find(playerE);
    if (p == world.positions.end()) return;
    const sf::Vector2f playerPos{ p->second.x, p->second.y };

    for (auto e : entities) {
        if (!world.enemies.contains(e)) continue;
        auto& enemy = world.enemies[e];

        if (enemy.respawnRequested) {
            enemy.respawnRequested = false;
            if (world.velocities.contains(e)) { world.velocities[e].dx = 0.f; world.velocities[e].dy = 0.f; }
            enemy.timeSinceSeen = 0.f;
            enemy.cooldownLeft  = 0.f;
            enemy.dashLeft      = 0.f;
            enemy.state = &PatrolState::instance();
        }

        if (!enemy.state) enemy.state = &PatrolState::instance();
        EnemyState* next = enemy.state->update(world, e, enemy, playerPos, dt);
        if (next != enemy.state) {
            enemy.state->exit(world, e, enemy);
            if (next) {
                enemy.state = next;
            } else {
                enemy.state = &PatrolState::instance();
            }
            enemy.state->enter(world, e, enemy);
        }
    }
}
