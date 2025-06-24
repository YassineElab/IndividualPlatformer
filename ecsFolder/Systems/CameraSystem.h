#ifndef INDIVIDUALPLATFORMER_CAMERASYSTEM_H

#include <SFML/Graphics.hpp>
#include "../System/Types.h"
#include "../System/System.h"

#define INDIVIDUALPLATFORMER_CAMERASYSTEM_H

class World;

class CameraSystem : public System {
public:
    void init(sf::RenderWindow& window) {
        if (!window.isOpen()) return;

        cameraView = window.getDefaultView();
        cameraView.setSize(1200.f, 600.f);
        window.setView(cameraView);
    }

    void update(World& world, sf::RenderWindow& window, Entity target);

private:
    sf::View cameraView;
};

#endif //INDIVIDUALPLATFORMER_CAMERASYSTEM_H