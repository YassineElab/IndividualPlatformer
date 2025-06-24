#ifndef INDIVIDUALPLATFORMER_MENUSTATE_H

#include "State.h"
#include "StateManager.h"
#include "../Factories/ConcreteFactory.h"
#include "LevelState.h"
#include "LevelMenuState.h"

#define INDIVIDUALPLATFORMER_MENUSTATE_H

class MenuState: public State{
private:
    sf::RenderWindow& renderWindow;
    float width;
    float height;
    StateManager& stateManager;
    sf::Sprite sprite;
    int menuSelect;
    sf::Font font;
    sf::Texture background;
    sf::Text menuScreen[8];

public:
    explicit MenuState(sf::RenderWindow& renderWindow1, StateManager& stateManager1, float width1, float height1);
    void draw() override;
    void update() override;
    void init() override;
    void inputController() override;
    void moveRight();
    void moveLeft();
};

#endif //INDIVIDUALPLATFORMER_MENUSTATE_H
