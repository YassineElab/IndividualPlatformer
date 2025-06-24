#ifndef INDIVIDUALPLATFORMER_LEVELSTATE_H

#include "State.h"
#include "StateManager.h"
#include "../Factories/ConcreteFactory.h"
#include "../World/World.h"

#define INDIVIDUALPLATFORMER_LEVELSTATE_H

class LevelState: public State{
private:
    sf::RenderWindow& renderWindow;
    float width;
    float height;
    StateManager& stateManager;
    std::unique_ptr<World> world;
    int levelId;

public:
    LevelState(sf::RenderWindow& renderWindow1, StateManager& stateManager1, float width1, float height1, int levelId1);
    void draw() override;
    void update() override;
    void init() override;
    void inputController() override;
};

#endif //INDIVIDUALPLATFORMER_LEVELSTATE_H
