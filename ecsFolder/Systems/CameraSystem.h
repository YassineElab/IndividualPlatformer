#ifndef INDIVIDUALPLATFORMER_CAMERASYSTEM_H

#include <SFML/Graphics.hpp>
#include "../System/Types.h"
#include "../System/System.h"

#define INDIVIDUALPLATFORMER_CAMERASYSTEM_H

class World;

class CameraSystem {
public:
    void init(sf::RenderWindow& window);
    void setBounds(const sf::FloatRect& worldBounds);

    void setZoom(float z);

    void snapToPlayer(World& world, sf::RenderWindow& window, Entity target);
    void update(World& world, sf::RenderWindow& window, Entity target);

private:
    sf::View cameraView{};
    sf::Vector2f baseViewSize{0.f,0.f};
    float zoom{1.f};

    sf::FloatRect bounds{0.f,0.f,0.f,0.f};
    bool hasBounds{false};

    float anchorX{0.25f};
    float anchorY{0.50f};

    float smooth{0.22f};
};

#endif //INDIVIDUALPLATFORMER_CAMERASYSTEM_H