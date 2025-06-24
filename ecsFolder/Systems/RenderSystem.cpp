#include "RenderSystem.h"
#include "../World/World.h"

void RenderSystem::update(World& world, sf::RenderWindow& window) {
    window.clear();
    window.draw(backgroundSprite);

    for (auto &[entity, renderable]: world.renderables) {
        if (world.positions.find(entity) != world.positions.end()) {
            auto &pos = world.positions[entity];
            renderable.shape.setPosition(
                    pos.x,
                    window.getSize().y - pos.y - renderable.shape.getSize().y
            );
            window.draw(renderable.shape);
        }
    }
}

void RenderSystem::init(sf::RenderWindow &window) {
    backgroundTexture.loadFromFile("ecsFolder/Resources/Pics/bg.jpg");
    backgroundSprite.setTexture(backgroundTexture);

    sf::Vector2u textureSize = backgroundTexture.getSize();
    sf::Vector2u windowSize = window.getSize();

    float scaleX = static_cast<float>(windowSize.x) / textureSize.x;
    float scaleY = static_cast<float>(windowSize.y+100) / textureSize.y;
    backgroundSprite.setScale(scaleX, scaleY);
}
