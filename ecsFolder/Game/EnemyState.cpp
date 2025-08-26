#include "EnemyState.h"
#include "../World/World.h"
#include <algorithm>
#include <cmath>

sf::Vector2f normalizeSafe(const sf::Vector2f& v) {
    float L2 = v.x*v.x + v.y*v.y;
    if (L2 <= 0.000001f) return {0.f, 0.f};
    float L = sqrt(L2);
    return { v.x / L, v.y / L };
}

sf::Vector2f goToward(const sf::Vector2f& target,
                                const sf::Vector2f& pos,
                                const sf::Vector2f& vel,
                                float maxSpeed, float accel, float dt)
{
    sf::Vector2f desired = normalizeSafe({ target.x - pos.x, target.y - pos.y });
    desired.x *= maxSpeed;
    desired.y *= maxSpeed;
    sf::Vector2f go{ desired.x - vel.x, desired.y - vel.y };
    float maxDelta = accel * dt;
    float s2 = go.x*go.x + go.y*go.y;
    if (s2 > maxDelta*maxDelta) {
        float s = sqrt(s2);
        go.x *= (maxDelta / s);
        go.y *= (maxDelta / s);
    }
    return go;
}

void clampVel(float& vx, float& vy, float maxSpeed) {
    float v = vx*vx + vy*vy, m2 = maxSpeed*maxSpeed;
    if (v > m2 && v > 0.000001f) {
        float k = maxSpeed / sqrt(v);
        vx *= k;
        vy *= k;
    }
}

PatrolState& PatrolState::instance() { static PatrolState s; return s; }

EnemyState* PatrolState::update(World& world, Entity e, Enemy& enemy,
                                const sf::Vector2f& playerPos, float dt)
{
    auto p = world.positions.find(e);
    auto v = world.velocities.find(e);
    if (p == world.positions.end() || v == world.velocities.end()) return this;

    auto& pos = p->second;
    auto& vel = v->second;

    sf::Vector2f p2{pos.x, pos.y};
    sf::Vector2f toPlayer{ playerPos.x - p2.x, playerPos.y - p2.y };
    float d2 = toPlayer.x*toPlayer.x + toPlayer.y*toPlayer.y;
    float seeRadius2 = enemy.seeRadius * enemy.seeRadius;

    if (d2 <= seeRadius2) {
        enemy.timeSinceSeen = 0.f;
    } else {
        enemy.timeSinceSeen += dt;
    }

    sf::Vector2f target;
    if (enemy.goingToB) {
        target = enemy.anchorB;
    } else {
        target = enemy.anchorA;
    }

    sf::Vector2f toT{ target.x - p2.x, target.y - p2.y };
    if (toT.x*toT.x + toT.y*toT.y < 64.f) enemy.goingToB = !enemy.goingToB;

    sf::Vector2f go = goToward(target, p2, {vel.dx, vel.dy}, enemy.maxSpeed, enemy.accel, dt);
    vel.dx += go.x;
    vel.dy += go.y;
    clampVel(vel.dx, vel.dy, enemy.maxSpeed);

    if (d2 <= seeRadius2) return &ChaseState::instance();
    return this;
}

ChaseState& ChaseState::instance() { static ChaseState s; return s; }

EnemyState* ChaseState::update(World& world, Entity e, Enemy& enemy,
                               const sf::Vector2f& playerPos, float dt)
{
    auto p = world.positions.find(e);
    auto v = world.velocities.find(e);
    if (p == world.positions.end() || v == world.velocities.end()) return this;

    auto& pos = p->second;
    auto& vel = v->second;

    sf::Vector2f p2{pos.x, pos.y};
    sf::Vector2f toPlayer{ playerPos.x - p2.x, playerPos.y - p2.y };
    float d2 = toPlayer.x*toPlayer.x + toPlayer.y*toPlayer.y;
    float seeRadius2 = enemy.seeRadius * enemy.seeRadius;
    float attackRange2 = enemy.attackRange * enemy.attackRange;

    if (d2 <= seeRadius2) {
        enemy.timeSinceSeen = 0.f;
    } else {
        enemy.timeSinceSeen += dt;
    }

    sf::Vector2f go = goToward(playerPos, p2, {vel.dx, vel.dy}, enemy.maxSpeed, enemy.accel, dt);
    vel.dx += go.x;
    vel.dy += go.y;
    clampVel(vel.dx, vel.dy, enemy.maxSpeed);

    if (d2 <= attackRange2 && enemy.cooldownLeft <= 0.f) {
        sf::Vector2f direction = normalizeSafe(toPlayer);
        vel.dx = direction.x * enemy.dashSpeed;
        vel.dy = direction.y * enemy.dashSpeed;
        enemy.dashLeft = enemy.dashTime;
        enemy.cooldownLeft = enemy.attackCooldown;
        return &AttackState::instance();
    }

    if (enemy.timeSinceSeen > enemy.loseSightTime) {
        return &PatrolState::instance();
    }

    if (enemy.cooldownLeft > 0.f) enemy.cooldownLeft = max(0.f, enemy.cooldownLeft - dt);
    return this;
}

AttackState& AttackState::instance() { static AttackState s; return s; }
void AttackState::enter(World&, Entity, Enemy&) {}

EnemyState* AttackState::update(World& world, Entity e, Enemy& enemy,
                                const sf::Vector2f& playerPos, float dt)
{
    auto p = world.positions.find(e);
    auto v = world.velocities.find(e);
    if (p == world.positions.end() || v == world.velocities.end()) return this;

    auto& pos = p->second;
    auto& vel = v->second;

    sf::Vector2f p2{pos.x, pos.y};
    sf::Vector2f toPlayer{ playerPos.x - p2.x, playerPos.y - p2.y };
    float d2 = toPlayer.x*toPlayer.x + toPlayer.y*toPlayer.y;
    float seeRadius2 = enemy.seeRadius * enemy.seeRadius;
    if (d2 <= seeRadius2) {
        enemy.timeSinceSeen = 0.f;
    } else {
        enemy.timeSinceSeen = enemy.timeSinceSeen + dt;
    }

    enemy.dashLeft = max(0.f, enemy.dashLeft - dt);
    enemy.cooldownLeft = max(0.f, enemy.cooldownLeft - dt);

    if (enemy.dashLeft <= 0.f) {
        float damp = clamp(1.f - 6.f * dt, 0.f, 1.f);
        vel.dx *= damp;
        vel.dy *= damp;

        if (enemy.cooldownLeft > 0.f) return &CooldownState::instance();
        if (d2 <= seeRadius2) return &ChaseState::instance();
        return &PatrolState::instance();
    }
    return this;
}

CooldownState& CooldownState::instance() { static CooldownState s; return s; }

EnemyState* CooldownState::update(World& world, Entity e, Enemy& enemy,
                                  const sf::Vector2f& playerPos, float dt)
{
    auto v = world.velocities.find(e);
    if (v == world.velocities.end()) return this;
    auto& vel = v->second;

    sf::Vector2f v2{vel.dx, vel.dy};
    sf::Vector2f go{-v2.x, -v2.y};
    float maxDelta = (enemy.accel * 0.6f) * dt;
    float s2 = go.x*go.x + go.y*go.y;
    if (s2 > maxDelta*maxDelta) {
        float s = sqrt(s2);
        go.x *= (maxDelta / s);
        go.y *= (maxDelta / s);
    }
    vel.dx += go.x; vel.dy += go.y;

    auto p = world.positions.find(e);
    if (p == world.positions.end()) return this;
    sf::Vector2f p2{p->second.x, p->second.y};
    sf::Vector2f toPlayer{ playerPos.x - p2.x, playerPos.y - p2.y };
    float d2 = toPlayer.x*toPlayer.x + toPlayer.y*toPlayer.y;
    float seeRadius2 = enemy.seeRadius * enemy.seeRadius;
    if (d2 <= seeRadius2) {
        enemy.timeSinceSeen = 0.f;
    } else {
        enemy.timeSinceSeen += dt;
    }

    enemy.cooldownLeft = max(0.f, enemy.cooldownLeft - dt);
    if (enemy.cooldownLeft <= 0.f) {
        if (d2 <= seeRadius2) return &ChaseState::instance();
        return &PatrolState::instance();
    }
    return this;
}
