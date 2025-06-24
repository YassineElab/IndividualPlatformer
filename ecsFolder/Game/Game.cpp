#include "game.h"
#include "../Factories/concreteFactory.h"
#include "Controller.h"
#include "MenuState.h"

shared_ptr<Stopwatch> Stopwatch::instance = 0;

Game::Game(int width, int height) {
    sf::RenderWindow window(sf::VideoMode(width, height), "Individual Platformer");
    window.setFramerateLimit(60);

    StateManager stateManager;
    Controller controller1(width, height, window, stateManager);

    stateManager.addState(shared_ptr<State>(new MenuState(window, stateManager, width, height)), true);

    while(controller1.isOpen()){
        stateManager.stateChanges();
        stateManager.getActiveState()->inputController();
        stateManager.getActiveState()->update();
    }
}