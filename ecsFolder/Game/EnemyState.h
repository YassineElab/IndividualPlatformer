#ifndef INDIVIDUALPLATFORMER_ENEMYSTATE_H

#include <SFML/Graphics.hpp>
#include "../System/Types.h"

#define INDIVIDUALPLATFORMER_ENEMYSTATE_H

struct Enemy;
class World;

class EnemyState {
public:
    virtual ~EnemyState() = default;
    virtual void enter(World&, Entity, Enemy&) {}
    virtual void exit(World&, Entity, Enemy&) {}
    virtual EnemyState* update(World&, Entity, Enemy&,
                               const sf::Vector2f& playerPos,
                               float dt) = 0;
};

class PatrolState : public EnemyState {
public:
    static PatrolState& instance();
    EnemyState* update(World&, Entity, Enemy&, const sf::Vector2f&, float dt) override;
private:
    PatrolState() = default;
    PatrolState(const PatrolState&) = delete;
    PatrolState& operator=(const PatrolState&) = delete;
};

class ChaseState : public EnemyState {
public:
    static ChaseState& instance();
    EnemyState* update(World&, Entity, Enemy&, const sf::Vector2f&, float dt) override;
private:
    ChaseState() = default;
    ChaseState(const ChaseState&) = delete;
    ChaseState& operator=(const ChaseState&) = delete;
};

class AttackState : public EnemyState {
public:
    static AttackState& instance();
    void enter(World&, Entity, Enemy&) override;
    EnemyState* update(World&, Entity, Enemy&, const sf::Vector2f&, float dt) override;
private:
    AttackState() = default;
    AttackState(const AttackState&) = delete;
    AttackState& operator=(const AttackState&) = delete;
};

class CooldownState : public EnemyState {
public:
    static CooldownState& instance();
    EnemyState* update(World&, Entity, Enemy&, const sf::Vector2f&, float dt) override;
private:
    CooldownState() = default;
    CooldownState(const CooldownState&) = delete;
    CooldownState& operator=(const CooldownState&) = delete;
};

#endif //INDIVIDUALPLATFORMER_ENEMYSTATE_H
