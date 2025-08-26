#include "CameraSystem.h"
#include "../World/World.h"

void CameraSystem::init(sf::RenderWindow& window) {
    cameraView = window.getDefaultView();
    baseViewSize = cameraView.getSize();
    cameraView.setSize(baseViewSize.x, -baseViewSize.y);
    window.setView(cameraView);
}

void CameraSystem::setBounds(const sf::FloatRect& worldBounds) {
    bounds = worldBounds;
    hasBounds = true;
}

void CameraSystem::setZoom(float z) {
    zoom = max(0.1f, z);
    cameraView.setSize(baseViewSize.x, -baseViewSize.y);
    cameraView.zoom(1.f / zoom);
}

void CameraSystem::snapToPlayer(World& world, sf::RenderWindow& window, Entity target) {
    auto t = world.positions.find(target);
    if (t == world.positions.end()) return;
    sf::Vector2f c(t->second.x, t->second.y);
    cameraView.setCenter(c);
    window.setView(cameraView);
}

void CameraSystem::update(World& world, sf::RenderWindow& window, Entity target) {
    auto t = world.positions.find(target);
    if (t == world.positions.end()) return;
    sf::Vector2f targetPos(t->second.x, t->second.y);

    sf::Vector2f center = cameraView.getCenter();
    sf::Vector2f desired = targetPos;
    sf::Vector2f smoothed = center + (desired - center) * smooth;

    cameraView.setCenter(smoothed);
    window.setView(cameraView);
}