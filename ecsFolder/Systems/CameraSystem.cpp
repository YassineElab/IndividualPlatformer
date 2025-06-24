#include "CameraSystem.h"
#include "../World/World.h"

void CameraSystem::update(World& world, sf::RenderWindow& window, Entity target) {

    auto& tf = world.transforms[target];

    float cameraX = max(tf.position.x, 600.f);
    float cameraY = max(tf.position.y, 400.f);

    cameraView.setCenter(cameraX, cameraY);
    window.setView(cameraView);
}