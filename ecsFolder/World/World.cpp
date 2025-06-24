#include "World.h"

World::World(ControllerV &controllerV1, AbstractFactory &abstractFactory1, sf::RenderWindow& window1, int levelId)
        : abstractFactory(abstractFactory1), controllerV(controllerV1), window(window1), projectileBuilder(*this, abstractFactory1), stopwatch(std::make_shared<Stopwatch>())
{
    for (Entity id = 0; id < 200; ++id) {
        availableEntities.push(id);
    }
    this->levelId = levelId;
}

Entity World::createEntity() {
    Entity id = availableEntities.front();
    availableEntities.pop();
    return id;
}

void World::startInit(){
    renderSystem = make_shared<RenderSystem>();
    inputSystem = make_shared<InputSystem>();
    movementSystem = make_shared<MovementSystem>();
    physicsSystem = make_shared<PhysicsSystem>();
    collisionSystem = make_shared<CollisionSystem>();
    cameraSystem = make_shared<CameraSystem>();
    jumpSystem = make_shared<JumpSystem>();
    projectileSystem = make_shared<ProjectileSystem>();
    shootSystem = make_shared<ShootSystem>(projectileBuilder);

    renderSystem->init(window);
    cameraSystem->init(window);
}

void World::init1() {
    startInit();
    hitTargets.clear();

    player = buildPlayer(50.f, -60.f, 30.f, 30.f);

    walls.push_back(buildWall(0, -100, 1250, 40));
    walls.push_back(buildWall(0, 495, 1250, 40));

    walls.push_back(buildWall(-35, -100, 40, 800));
    walls.push_back(buildWall(1195, -100, 40, 800));

    walls.push_back(buildWall(150, -60, 100, 30));
    walls.push_back(buildWall(250, -60, 100, 60));
    walls.push_back(buildWall(350, -60, 100, 90));
    walls.push_back(buildWall(450, -60, 100, 120));

    targetsE.push_back(buildTarget(700, 90, 30, 30));
    targetsE.push_back(buildTarget(650, 380, 30, 30));
    targetsE.push_back(buildTarget(950, 440, 30, 30));

    walls.push_back(buildWall(800, -20, 20, 720));
    walls.push_back(buildWall(900, -60, 20, 400));
    walls.push_back(buildWall(900, 340, 300, 20));

    goal = buildGoal(1100, 360, 60, 60);
}

void World::init2() {
    startInit();
    hitTargets.clear();

    player = buildPlayer(50.f, -60.f, 30.f, 30.f);

    walls.push_back(buildWall(0, -100, 1250, 40));
    walls.push_back(buildWall(0, 495, 1250, 40));

    walls.push_back(buildWall(-35, -100, 40, 800));
    walls.push_back(buildWall(1195, -100, 40, 800));

    springsE.push_back(buildSpring(200, -60, 20.f, 20.f));

    walls.push_back(buildWall(230, -60, 120, 80));
    spikesE.push_back(buildSpike(240, 20, 20.f, 20.f));
    spikesE.push_back(buildSpike(260, 20, 20.f, 20.f));
    spikesE.push_back(buildSpike(280, 20, 20.f, 20.f));
    spikesE.push_back(buildSpike(300, 20, 20.f, 20.f));
    springsE.push_back(buildSpring(325, 20, 20.f, 20.f));

    walls.push_back(buildWall(350, -60, 40, 180));


    targetsE.push_back(buildTarget(200, 140, 40.f, 40.f));

    walls.push_back(buildWall(490, 100, 60, 20));

    targetsE.push_back(buildTarget(500, 20, 40.f, 40.f));
    targetsE.push_back(buildTarget(720, 120, 40.f, 40.f));

    springsE.push_back(buildSpring(800, -60, 20, 20));

    spikesE.push_back(buildSpike(830, -60, 20.f, 20.f));
    spikesE.push_back(buildSpike(850, -60, 20.f, 20.f));
    spikesE.push_back(buildSpike(870, -60, 20.f, 20.f));
    spikesE.push_back(buildSpike(890, -60, 20.f, 20.f));
    spikesE.push_back(buildSpike(910, -60, 20.f, 20.f));
    spikesE.push_back(buildSpike(930, -60, 20.f, 20.f));
    spikesE.push_back(buildSpike(950, -60, 20.f, 20.f));
    spikesE.push_back(buildSpike(970, -60, 20.f, 20.f));
    spikesE.push_back(buildSpike(990, -60, 20.f, 20.f));

    goal = buildGoal(1000, -20, 60, 60);
}

void World::init3() {
    startInit();
    hitTargets.clear();

    player = buildPlayer(50.f, -60.f, 30.f, 30.f);

    walls.push_back(buildWall(0, -100, 1250, 40));
    walls.push_back(buildWall(0, 495, 1250, 40));

    walls.push_back(buildWall(-35, -60, 40, 800));
    walls.push_back(buildWall(1195, -60, 40, 800));

    walls.push_back(buildWall(130, -60, 10, 460));

    springsE.push_back(buildSpring(105, -60, 20, 20));
    spikesE.push_back(buildSpike(105, 60, 20, 20));
    walls.push_back(buildWall(95, 50, 40, 10));

    springsE.push_back(buildSpring(15, 40, 20, 20));

    springsE.push_back(buildSpring(105, 160, 20, 20));
    spikesE.push_back(buildSpike(105, 280, 20, 20));
    walls.push_back(buildWall(95, 270, 40, 10));

    springsE.push_back(buildSpring(15, 270, 20, 20));

    walls.push_back(buildWall(130, 400, 280, 10));

    targetsE.push_back(buildTarget(210, 320, 40, 40));

    walls.push_back(buildWall(500, 200, 10, 300));
    walls.push_back(buildWall(280, 200, 220, 10));
    spikesE.push_back(buildSpike(340, 210, 20, 20));
    spikesE.push_back(buildSpike(360, 210, 20, 20));
    spikesE.push_back(buildSpike(380, 210, 20, 20));
    spikesE.push_back(buildSpike(400, 210, 20, 20));
    spikesE.push_back(buildSpike(420, 210, 20, 20));
    spikesE.push_back(buildSpike(440, 210, 20, 20));
    spikesE.push_back(buildSpike(460, 210, 20, 20));
    spikesE.push_back(buildSpike(480, 210, 20, 20));

    walls.push_back(buildWall(280, 100, 10, 100));
    walls.push_back(buildWall(220, 100, 60, 10));
    spikesE.push_back(buildSpike(220, 110, 20, 20));
    spikesE.push_back(buildSpike(240, 110, 20, 20));
    spikesE.push_back(buildSpike(260, 110, 20, 20));

    spikesE.push_back(buildSpike(150, -60, 40, 40));
    spikesE.push_back(buildSpike(190, -60, 40, 40));
    spikesE.push_back(buildSpike(230, -60, 40, 40));
    spikesE.push_back(buildSpike(270, -60, 40, 40));
    spikesE.push_back(buildSpike(310, -60, 40, 40));
    spikesE.push_back(buildSpike(350, -60, 40, 40));
    spikesE.push_back(buildSpike(390, -60, 40, 40));
    spikesE.push_back(buildSpike(430, -60, 40, 40));
    spikesE.push_back(buildSpike(470, -60, 40, 40));
    spikesE.push_back(buildSpike(510, -60, 40, 40));
    spikesE.push_back(buildSpike(550, -60, 40, 40));

    spikesE.push_back(buildSpike(710, -60, 40, 40));
    spikesE.push_back(buildSpike(750, -60, 40, 40));
    spikesE.push_back(buildSpike(790, -60, 40, 40));
    spikesE.push_back(buildSpike(830, -60, 40, 40));
    spikesE.push_back(buildSpike(870, -60, 40, 40));
    spikesE.push_back(buildSpike(910, -60, 40, 40));
    spikesE.push_back(buildSpike(950, -60, 40, 40));
    spikesE.push_back(buildSpike(990, -60, 40, 40));
    spikesE.push_back(buildSpike(1030, -60, 40, 40));
    spikesE.push_back(buildSpike(1070, -60, 40, 40));
    spikesE.push_back(buildSpike(1110, -60, 40, 40));
    spikesE.push_back(buildSpike(1150, -60, 40, 40));

    walls.push_back(buildWall(190, 15, 40, 10));
    walls.push_back(buildWall(310, 35, 40, 10));
    walls.push_back(buildWall(420, 100, 40, 10));

    walls.push_back(buildWall(600, -60, 10, 460));
    walls.push_back(buildWall(560, 120, 40, 10));
    springsE.push_back(buildSpring(580, 130, 20, 20));

    walls.push_back(buildWall(600, 400, 70, 10));
    walls.push_back(buildWall(770, 400, 70, 10));
    walls.push_back(buildWall(940, 400, 50, 10));

    walls.push_back(buildWall(600, 300, 400, 15));

    spikesE.push_back(buildSpike(625, 310, 40, 40));
    spikesE.push_back(buildSpike(665, 310, 40, 40));
    spikesE.push_back(buildSpike(705, 310, 40, 40));
    spikesE.push_back(buildSpike(745, 310, 40, 40));
    spikesE.push_back(buildSpike(785, 310, 40, 40));
    spikesE.push_back(buildSpike(825, 310, 40, 40));
    spikesE.push_back(buildSpike(865, 310, 40, 40));
    spikesE.push_back(buildSpike(905, 310, 40, 40));
    spikesE.push_back(buildSpike(945, 310, 40, 40));

    targetsE.push_back(buildTarget(800, 250, 40, 40));

    walls.push_back(buildWall(770, 100, 420, 10));
    springsE.push_back(buildSpring(990, 160, 20, 20));

    spikesE.push_back(buildSpike(870, 110, 40, 40));
    spikesE.push_back(buildSpike(910, 110, 40, 40));
    spikesE.push_back(buildSpike(950, 110, 40, 40));
    spikesE.push_back(buildSpike(990, 110, 40, 40));
    spikesE.push_back(buildSpike(1030, 110, 40, 40));
    spikesE.push_back(buildSpike(1070, 110, 40, 40));
    spikesE.push_back(buildSpike(1110, 110, 40, 40));
    spikesE.push_back(buildSpike(1150, 110, 40, 40));

    walls.push_back(buildWall(700, -60, 10, 210));

    targetsE.push_back(buildTarget(620, -20, 40, 40));
    spikesE.push_back(buildSpike(615, -60, 20, 20));
    spikesE.push_back(buildSpike(635, -60, 20, 20));
    spikesE.push_back(buildSpike(655, -60, 20, 20));
    spikesE.push_back(buildSpike(675, -60, 20, 20));

    walls.push_back(buildWall(870, 0, 40, 10));
    walls.push_back(buildWall(1020, 0, 40, 10));

    goal = buildGoal(1140, -20, 60, 60);

}

void World::init() {
    switch (levelId) {
        case 1: init1(); break;
        case 2: init2(); break;
        case 3: init3(); break;
        default: init1(); break;
    }
}

void World::update() {
    if (!stopwatch) return;

    this->stopwatch->nextFrame();
    float movementMul = this->stopwatch->getMovementMultiplier();

    if (inputSystem) inputSystem->update(*this);
    if (movementSystem) movementSystem->update(*this, movementMul);
    if (physicsSystem) physicsSystem->update(*this, movementMul);
    if (jumpSystem) jumpSystem->update(*this);
    if (projectileSystem) projectileSystem->update(*this, movementMul);
    if (shootSystem) shootSystem->update(*this, movementMul);
    if (collisionSystem) collisionSystem->update(*this, collisionTree);
    if (cameraSystem) cameraSystem->update(*this, window, player);
    if (renderSystem) renderSystem->update(*this, window);
}

void World::gameLoop() {
    while (controllerV.isOpen() && window.isOpen() && !goNextLevel) {
        controllerV.checkForClose();

        window.clear(sf::Color::White);

        this->update();

        window.display();
    }
}

Entity World::buildPlayer(float x, float y, float width, float height) {
    Entity player = PlayerBuilder(*this, abstractFactory)
            .makePlayer(x, y, width, height)
            .build();

    if (collisionSystem) {
        collisionSystem->AddEntity(player, *this);
    }
    if (inputSystem) {
        inputSystem->AddEntity(player, *this);
    }
    if (movementSystem) {
        movementSystem->AddEntity(player, *this);
    }
    if (physicsSystem) {
        physicsSystem->AddEntity(player, *this);
    }
    if (jumpSystem) {
        jumpSystem->AddEntity(player, *this);
    }
    if (shootSystem) {
        shootSystem->AddEntity(player, *this);
    }

    return player;
}


Entity World::buildWall(float x, float y, float width, float height) {
    Entity wall = WallBuilder(*this, abstractFactory)
            .makeWall(x, y, width, height)
            .build();

    if (collisionSystem) {
        collisionSystem->AddEntity(wall, *this);
    }

    return wall;
}


Entity World::buildSpring(float x, float y, float width, float height) {
    Entity spring = SpringBuilder(*this, abstractFactory)
            .makeSpring(x, y, width, height)
            .build();

    if (collisionSystem) {
        collisionSystem->AddEntity(spring, *this);
    }

    return spring;
}

Entity World::buildSpike(float x, float y, float width, float height) {
    Entity spring = SpikeBuilder(*this, abstractFactory)
            .makeSpike(x, y, width, height)
            .build();

    if (collisionSystem) {
        collisionSystem->AddEntity(spring, *this);
    }

    return spring;
}

Entity World::buildGoal(float x, float y, float width, float height) {
    Entity goal = GoalBuilder(*this, abstractFactory)
            .makeGoal(x, y, width, height)
            .build();

    if (collisionSystem) {
        collisionSystem->AddEntity(goal, *this);
    }

    return goal;
}

Entity World::buildTarget(float x, float y, float width, float height) {
    Entity target = TargetBuilder(*this, abstractFactory)
            .makeTarget(x, y, width, height)
            .build();

    if (collisionSystem) {
        collisionSystem->AddEntity(target, *this);
    }

    return target;
}

bool World::getNextLevel() {
    return goNextLevel;
}

void World::setNextLevel(bool next) {
    goNextLevel = next;
}

void World::destroyEntity(Entity entity) {
    positions.erase(entity);
    velocities.erase(entity);
    colliders.erase(entity);
    projectiles.erase(entity);

    availableEntities.push(entity);
}

