#include "Controller.h"

Controller::Controller(int width, int height, sf::RenderWindow& window, StateManager& stateManager1): stateManager(stateManager1), renderWindow(window), width(width), height(height) {

}

bool Controller::isOpen() {
    return this->renderWindow.isOpen();
}

void Controller::checkForClose() {
    sf::Event event;
    renderWindow.pollEvent(event);
    if(event.type == sf::Event::Closed){
        this->renderWindow.close();
    }
}