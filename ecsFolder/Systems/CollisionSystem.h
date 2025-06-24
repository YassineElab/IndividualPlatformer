#ifndef INDIVIDUALPLATFORMER_COLLISIONSYSTEM_H

#include "../System/Types.h"
#include "../System/System.h"
#include "../Components/Components.h"
#include "../Collision/Quadtree.h"
#include <SFML/Graphics.hpp>

#define INDIVIDUALPLATFORMER_COLLISIONSYSTEM_H

class World;

class CollisionSystem : public System {
private:
    bool resolveWallCollision(Position& position, Velocity* velocity,
                              sf::FloatRect& bounds, const sf::FloatRect& wall, bool* onLeftWall, bool* onRightWall) {
        sf::FloatRect adjustedBounds = bounds;
        adjustedBounds.top += 1.f;
        adjustedBounds.height += 1.f;

        sf::FloatRect intersection;
        if (!adjustedBounds.intersects(wall, intersection)) {
            return false;
        }

        if (intersection.width < intersection.height) {
            if (bounds.left < wall.left) {
                position.x -= intersection.width;
                if (onRightWall) *onRightWall = true;
            } else {
                position.x += intersection.width;
                if (onLeftWall) *onLeftWall = true;
            }
            bounds.left = position.x;
            if (velocity) velocity->dx = 0;
            return false;
        } else {
            bool falling = velocity && velocity->dy > 0;
            float playerBottom = bounds.top;
            float wallTop = wall.top;

            bool hitFromAbove = !falling && (playerBottom - (wallTop + wall.height) <= intersection.height + 0.1f);

            if (hitFromAbove) {
                position.y += intersection.height;
            } else {
                position.y -= intersection.height;
            }

            bounds.top = position.y;
            if (velocity) velocity->dy = 0;

            return hitFromAbove;
        }
    }

    bool resolveSpringCollision(Position& position, Velocity* velocity,
                                sf::FloatRect& bounds, const sf::FloatRect& springBounds,
                                const Spring& spring) {
        sf::FloatRect adjustedBounds = bounds;
        adjustedBounds.top += 1.f;
        adjustedBounds.height += 1.f;

        sf::FloatRect intersection;
        if (!adjustedBounds.intersects(springBounds, intersection)) {
            return false;
        }

        if (intersection.width < intersection.height) {
            if (bounds.left < springBounds.left) {
                position.x -= intersection.width;
            } else {
                position.x += intersection.width;
            }
            bounds.left = position.x;
            if (velocity) velocity->dx = 0;
            return false;
        } else {
            bool falling = velocity && velocity->dy > 0;
            float playerBottom = bounds.top;
            float springTop = springBounds.top + springBounds.height;

            bool hitFromAbove = !falling && (playerBottom - (springTop + springBounds.height) <= intersection.height + 0.1f);

            if (hitFromAbove) {
                position.y += intersection.height;
                if (velocity) velocity->dy = spring.bounceImpulse;
                return true;
            } else {
                position.y += intersection.height;
                bounds.top = position.y;
                if (velocity) velocity->dy = 0;
                return false;
            }
        }
    }

    bool resolveSpikeCollision(const sf::FloatRect& playerBounds, const sf::FloatRect& spikeBounds) {
        return playerBounds.intersects(spikeBounds);
    }

    bool resolveProjectileCollision(Position& position, sf::FloatRect& projectileBounds, const sf::FloatRect& wallBounds) {
        sf::FloatRect intersection;
        if (!projectileBounds.intersects(wallBounds, intersection)) {
            return false;
        }
        return true;
    }


public:
    void AddEntity(Entity entity, World& world);

    void update(World& world, Quadtree& quadtree);
};

#endif //INDIVIDUALPLATFORMER_COLLISIONSYSTEM_H