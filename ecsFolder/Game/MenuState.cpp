#include "MenuState.h"
#include "iostream"

MenuState::MenuState(sf::RenderWindow &renderWindow1, StateManager &stateManager1, float width1, float height1): renderWindow(renderWindow1), stateManager(stateManager1) {
    width = width1;
    height = height1;
    menuSelect = 0;
}

void MenuState::draw() {
    renderWindow.clear();
    renderWindow.draw(sprite);
    for(int i = 0; i < 4;i++){
        renderWindow.draw(menuScreen[i]);
    }
    renderWindow.display();
}

void MenuState::update() {
    draw();
}


void MenuState::init() {
    if(!font.loadFromFile("./ecsFolder/Resources/Fonts/arial.ttf") or !background.loadFromFile("./ecsFolder/Resources/Pics/image.jpg")){
        cout << "File not loaded!" << endl;
    }

    sprite.setTexture(background);
    sprite.setTextureRect(sf::IntRect(0, 40, width, height));

    menuScreen[0].setString("PLAY");
    menuScreen[0].setFont(font);
    menuScreen[0].setFillColor(sf::Color::Green);
    menuScreen[0].setPosition(width / 2 -150, height / 6);

    menuScreen[1].setString("EXIT");
    menuScreen[1].setFont(font);
    menuScreen[1].setFillColor(sf::Color::Black);
    menuScreen[1].setPosition(width / 2 + 50, height / 6);
}

void MenuState::moveRight() {
    if(menuSelect + 1 < 2){
        menuScreen[menuSelect].setFillColor(sf::Color::Black);
        menuSelect += 1;
        menuScreen[menuSelect].setFillColor(sf::Color::Green);
    }

}

void MenuState::moveLeft() {
    if(menuSelect - 1 >= 0){
        menuScreen[menuSelect].setFillColor(sf::Color::Black);
        menuSelect -= 1;
        menuScreen[menuSelect].setFillColor(sf::Color::Green);
    }
}

void MenuState::inputController() {
    sf::Event event;
    while(renderWindow.pollEvent(event)){
        if(event.type == sf::Event::Closed){
            renderWindow.close();
        }
        if(event.type == sf::Event::KeyPressed){
            if(event.key.code == sf::Keyboard::Key::Right){
                moveRight();
            }
            if(event.key.code == sf::Keyboard::Key::Left){
                moveLeft();
            }
            if(event.key.code == sf::Keyboard::Key::Return){
                if(menuSelect == 0){
                    stateManager.addState(make_shared<LevelMenuState>(renderWindow, stateManager, width, height), false);
                }
                else if(menuSelect == 1){
                    renderWindow.close();
                }
            }
        }
    }
}
