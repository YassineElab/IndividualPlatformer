#ifndef INDIVIDUALPLATFORMER_CONTROLLER_H

#include "ControllerV.h"
#include <SFML/Graphics.hpp>
#include "StateManager.h"

#define INDIVIDUALPLATFORMER_CONTROLLER_H

class Controller : public ControllerV {
private:
    sf::RenderWindow& renderWindow;
    int width, height;
    StateManager& stateManager;

public:
    Controller(int width, int height, sf::RenderWindow& window, StateManager& stateManager1);

    bool isOpen() override;
    void checkForClose() override;
};

#endif //INDIVIDUALPLATFORMER_CONTROLLER_H