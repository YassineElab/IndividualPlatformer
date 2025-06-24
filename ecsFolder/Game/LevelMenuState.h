#ifndef INDIVIDUALPLATFORMER_LEVELMENUSTATE_H

#include "LevelState.h"
#include "fstream"
#define MAX 8

#define INDIVIDUALPLATFORMER_LEVELMENUSTATE_H


class LevelMenuState: public State{
private:
    sf::RenderWindow& renderWindow;
    StateManager& stateManager;
    float width;
    float height;
    int numberOfLevels = 0;
    bool play;
    sf::Font font;
    sf::Sprite sprite;
    sf::Texture background;
    sf::Text menuScreen[MAX];
    int menuSelect;

public:
    explicit LevelMenuState(sf::RenderWindow& renderWindow1, StateManager& stateManager1, float width1, float height1);
    void draw() override;
    void update() override;
    void init() override;
    void inputController() override;
    void moveUpward();
    void moveDownward();
};;


#endif //INDIVIDUALPLATFORMER_LEVELMENUSTATE_H
