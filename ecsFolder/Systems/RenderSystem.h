#ifndef INDIVIDUALPLATFORMER_RENDERSYSTEM_H

#include "../System/Types.h"
#include "../System/System.h"
#include "../Game/ControllerV.h"
#include "../Systems/CameraSystem.h"
#include "../Components/Components.h"
#include <SFML/Graphics.hpp>

#define INDIVIDUALPLATFORMER_RENDERSYSTEM_H

class World;

class RenderSystem : public System {
private:
    sf::Texture backgroundTexture;
    sf::Sprite backgroundSprite;

public:
    void init(sf::RenderWindow& window);
    void update(World& world, sf::RenderWindow& window);

    sf::Texture heartTexture;
    bool heartTextureLoaded = false;
    float heartScale = 1.f;

    void drawHUD(World& world, sf::RenderWindow& window);
};

#endif //INDIVIDUALPLATFORMER_RENDERSYSTEM_H