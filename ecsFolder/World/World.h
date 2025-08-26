#ifndef INDIVIDUALPLATFORMER_WORLD_H

#include <memory>
#include <queue>
#include "../Factories/AbstractFactory.h"
#include "./Stopwatch.h"
#include "../Game/ControllerV.h"
#include "../System/Types.h"
#include "../Components/Components.h"
#include "../Builder/PlayerBuilder.h"
#include "../Builder/WallBuilder.h"
#include "../Builder/SpringBuilder.h"
#include "../Builder/SpikeBuilder.h"
#include "../Builder/GoalBuilder.h"
#include "../Builder/TargetBuilder.h"
#include "../Builder/EnemyBuilder.h"
#include "../Systems/RenderSystem.h"
#include "../Systems/MovementSystem.h"
#include "../Systems/InputSystem.h"
#include "../Systems/PhysicsSystem.h"
#include "../Systems/CollisionSystem.h"
#include "../Systems/CameraSystem.h"
#include "../Systems/JumpSystem.h"
#include "../Systems/ProjectileSystem.h"
#include "../Systems/ShootSystem.h"
#include "../Systems/EnemySystem.h"
#include "../Collision/Quadtree.h"

#define INDIVIDUALPLATFORMER_WORLD_H

class World {
private:
    ControllerV& controllerV;
    AbstractFactory& abstractFactory;
    sf::RenderWindow& window;

    shared_ptr<RenderSystem> renderSystem;
    shared_ptr<InputSystem> inputSystem ;
    shared_ptr<MovementSystem> movementSystem;
    shared_ptr<PhysicsSystem> physicsSystem;
    shared_ptr<CollisionSystem> collisionSystem;
    shared_ptr<CameraSystem> cameraSystem;
    shared_ptr<JumpSystem> jumpSystem;
    shared_ptr<ProjectileSystem> projectileSystem;
    shared_ptr<ShootSystem> shootSystem;
    shared_ptr<EnemySystem> enemySystem;

    Quadtree collisionTree{0, sf::FloatRect(0, 0, 1200, 600)};

    shared_ptr<Stopwatch> stopwatch = Stopwatch::getInstance();
    Entity player;
    vector<Entity> walls;
    vector<Entity> springsE;
    vector<Entity> spikesE;
    vector<Entity> projectilesE;
    vector<Entity> targetsE;
    vector<Entity> enemiesE;
    Entity goal;
    queue<Entity> availableEntities;

    bool goNextLevel = false;
    int levelId = 0;

    ProjectileBuilder projectileBuilder;

    sf::FloatRect worldBounds;
public:
    World(ControllerV& controllerV, AbstractFactory& abstractFactory1, sf::RenderWindow& window1, int levelId);

    void init();
    void init1();
    void init2();
    void init3();
    void startInit();
    void gameLoop();
    void update();

    Entity buildPlayer(float x, float y, float width, float height);
    Entity buildWall(float x, float y, float width, float height);
    Entity buildSpring(float x, float y, float width, float height);
    Entity buildSpike(float x, float y, float width, float height);
    Entity buildGoal(float x, float y, float width, float height);
    Entity buildTarget(float x, float y, float width, float height);
    Entity buildEnemy(float x, float y, float width, float height, sf::Vector2f A, sf::Vector2f B);

    Entity createEntity();
    void destroyEntity(Entity entity);

    unordered_map<Entity, Position> positions;
    unordered_map<Entity, Size> sizes;
    unordered_map<Entity, Renderable> renderables;
    unordered_map<Entity, Velocity> velocities;
    unordered_map<Entity, Collider> colliders;
    unordered_map<Entity, Gravity> gravities;
    unordered_map<Entity, MovementInput> movementInputs;
    unordered_map<Entity, Jump> jumps;
    unordered_map<Entity, Transform> transforms;
    unordered_map<Entity, PlayerTag> playerTags;
    unordered_map<Entity, WallTag> wallTags;
    unordered_map<Entity, SpringTag> springTags;
    unordered_map<Entity, Spring> springs;
    unordered_map<Entity, SpikeTag> spikeTags;
    unordered_map<Entity, Spike> spikes;
    unordered_map<Entity, GoalTag> goalTags;
    unordered_map<Entity, Projectile> projectiles;
    unordered_map<Entity, ProjectileTag> projectileTags;
    unordered_map<Entity, Shooting> shooting;
    unordered_map<Entity, TargetTag> targetTags;
    unordered_map<Entity, Target> targets;
    vector<Target> hitTargets;
    unordered_map<Entity, Enemy> enemies;
    unordered_map<Entity, EnemyTag> enemyTags;
    unordered_map<Entity, Health>   healths;

    bool restartRequested = false;

    float frameDt = 0.f;

    void clearAllEntities();

    void setNextLevel(bool next);
    bool getNextLevel();
    AbstractFactory& getAbstractFactory() {return abstractFactory;}
    shared_ptr<ProjectileSystem> getProjectileSystem() {return projectileSystem;}
    ProjectileBuilder getProjectileBuilder() {return projectileBuilder;}
};

#endif //INDIVIDUALPLATFORMER_WORLD_H
