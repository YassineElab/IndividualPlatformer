#include "LevelMenuState.h"
#include "LevelState.h"
#include "iostream"

LevelMenuState::LevelMenuState(sf::RenderWindow& renderWindow1, StateManager& stateManager1, float width1, float height1): renderWindow(renderWindow1), stateManager(stateManager1) {
    width = width1;
    height = height1;
    play = false;
    menuSelect = 1;
    numberOfLevels = 3;
}

void LevelMenuState::draw() {
    renderWindow.clear();
    renderWindow.draw(sprite);
    if(!play){
        for(int i = 0; i < MAX; ++i){
            renderWindow.draw(menuScreen[i]);
        }
    }
    renderWindow.display();
}

void LevelMenuState::update() {
    draw();
}

void LevelMenuState::init() {
    if(!font.loadFromFile("./ecsFolder/Resources/Fonts/arial.ttf") or !background.loadFromFile("./ecsFolder/Resources/Pics/image.jpg")){
        cout << "File not loaded!" << endl;
    }

    sprite.setTexture(background);
    sprite.setTextureRect(sf::IntRect(0, 30, width, height));

    for(int i = 1; i <= numberOfLevels+1; i++){
        string level_return;
        if(i != numberOfLevels+1){
            level_return = "Level" + to_string(i);
        }else if(i == numberOfLevels+1){
            level_return = "Return";
        }
        menuScreen[i].setString(level_return);
        menuScreen[i].setFont(font);

        if(i == 1){
            menuScreen[i].setFillColor(sf::Color::Green);
        }
        else{
            menuScreen[i].setFillColor(sf::Color::Black);
        }

        menuScreen[i].setPosition(width / 2 - 60, height / MAX * i + 200);
    }
}

void LevelMenuState::inputController() {
    sf::Event event;
    while (renderWindow.pollEvent(event)) {
        if (event.type == sf::Event::Closed) {
            renderWindow.close();
        }
        if (event.type == sf::Event::KeyPressed) {
            if (event.key.code == sf::Keyboard::Key::Up) {
                moveUpward();
            }
            if (event.key.code == sf::Keyboard::Key::Down) {
                moveDownward();
            }
            if (event.key.code == sf::Keyboard::Key::Return) {
                if (menuSelect <= numberOfLevels) {
                    stateManager.addState(std::make_shared<LevelState>(
                            renderWindow, stateManager, width, height, menuSelect));
                } else if (menuSelect == numberOfLevels + 1 && !play) {
                    stateManager.removeState();
                }
            }
        }
    }
}

void LevelMenuState::moveUpward() {
    if(menuSelect - 1 >= 1){
        menuScreen[menuSelect].setFillColor(sf::Color::Black);
        menuSelect -= 1;
        menuScreen[menuSelect].setFillColor(sf::Color::Green);
    }
}

void LevelMenuState::moveDownward() {
    if(menuSelect + 1 <= numberOfLevels + 1){
        menuScreen[menuSelect].setFillColor(sf::Color::Black);
        menuSelect += 1;
        menuScreen[menuSelect].setFillColor(sf::Color::Green);
    }
}