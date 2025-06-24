#include "LevelState.h"
#include "../Game/controller.h"

LevelState::LevelState(sf::RenderWindow& renderWindow1, StateManager &stateManager1, float width1, float height1, int levelId1): renderWindow(renderWindow1), stateManager(stateManager1) {
    width = width1;
    height = height1;
    levelId = levelId1;
}

void LevelState::draw() {

}

void LevelState::update() {
    ConcreteFactory concreteFactory(renderWindow);
    Controller controller1(width, height, renderWindow, stateManager);
    World world(controller1, concreteFactory, renderWindow, levelId);
    world.init();
    world.gameLoop();

    if(world.getNextLevel()){
        stateManager.addState(make_shared<LevelState>(renderWindow, stateManager, width, height, levelId + 1));
        world.setNextLevel(false);
    }
}

void LevelState::init() {
}

void LevelState::inputController() {

}

