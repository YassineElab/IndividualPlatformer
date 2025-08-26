#include "RenderSystem.h"
#include "../World/World.h"

void RenderSystem::update(World& world, sf::RenderWindow& window) {
    const sf::View worldView = window.getView();
    window.setView(window.getDefaultView());
    window.draw(backgroundSprite);
    window.setView(worldView);

    for (auto &[entity, renderable]: world.renderables) {
        if (world.positions.find(entity) == world.positions.end()) continue;
        auto &pos = world.positions[entity];
        renderable.shape.setPosition(pos.x, pos.y);
        window.draw(renderable.shape);
    }

    drawHUD(world, window);
}

void RenderSystem::init(sf::RenderWindow &window) {
    backgroundTexture.loadFromFile("../ecsFolder/Resources/Pics/bg.jpg");
    backgroundSprite.setTexture(backgroundTexture);

    sf::Vector2u textureSize = backgroundTexture.getSize();
    sf::Vector2u windowSize = window.getSize();

    float scaleX = static_cast<float>(windowSize.x) / textureSize.x;
    float scaleY = static_cast<float>(windowSize.y+100) / textureSize.y;
    backgroundSprite.setScale(scaleX, scaleY);

    if (heartTexture.loadFromFile("../ecsFolder/Resources/Pics/heart.png")) {
        heartTextureLoaded = true;
        const float targetPx = 24.f;
        heartScale = targetPx / static_cast<float>(heartTexture.getSize().x);
    }else{
        heartTextureLoaded = false;
        heartScale = 1.f;
    }
}

void RenderSystem::drawHUD(World& world, sf::RenderWindow& window) {
    if (world.playerTags.empty()) return;
    const Entity playerE = world.playerTags.begin()->first;
    auto p = world.healths.find(playerE);
    if (p == world.healths.end()) return;

    int hp = p->second.hp;
    const int maxHearts = 3;
    if (hp < 0) hp = 0;
    if (hp > maxHearts) hp = maxHearts;

    const float margin = 10.f;
    const float spacing = 8.f;

    window.setView(window.getDefaultView());

    if (heartTextureLoaded) {
        for (int i = 0; i < maxHearts; ++i) {
            sf::Sprite s(heartTexture);
            s.setScale(heartScale, heartScale);
            sf::Vector2u tex = heartTexture.getSize();
            float w = tex.x * heartScale;
            float x = margin + i * (w + spacing);
            s.setPosition(x, margin);
            if (i >= hp) s.setColor(sf::Color(255, 255, 255, 80));
            window.draw(s);
        }
    } else {
        const sf::Vector2f sz(24.f, 24.f);
        for (int i = 0; i < maxHearts; ++i) {
            sf::RectangleShape r(sz);
            float x = margin + i * (sz.x + spacing);
            r.setPosition(x, margin);
            if (i < hp) {
                r.setFillColor(sf::Color(220, 0, 0));
            } else {
                r.setFillColor(sf::Color(90, 90, 90));
            }
            window.draw(r);
        }
    }
}
