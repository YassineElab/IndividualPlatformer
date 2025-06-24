#ifndef INDIVIDUALPLATFORMER_QUADTREE_H

#include <vector>
#include <memory>
#include <SFML/Graphics.hpp>

#define INDIVIDUALPLATFORMER_QUADTREE_H

class Quadtree {
private:
    void split() {
        float subWidth = bounds.width / 2;
        float subHeight = bounds.height / 2;
        float x = bounds.left;
        float y = bounds.top;

        nodes[0] = make_unique<Quadtree>(level+1, sf::FloatRect(x + subWidth, y, subWidth, subHeight));
        nodes[1] = make_unique<Quadtree>(level+1, sf::FloatRect(x, y, subWidth, subHeight));
        nodes[2] = make_unique<Quadtree>(level+1, sf::FloatRect(x, y + subHeight, subWidth, subHeight));
        nodes[3] = make_unique<Quadtree>(level+1, sf::FloatRect(x + subWidth, y + subHeight, subWidth, subHeight));
    }

    int getIndex(sf::FloatRect rect) {
        int index = -1;
        float vMidPoint = bounds.left + (bounds.width / 2);
        float hMidpoint = bounds.top + (bounds.height / 2);

        bool topQuadrant = (rect.top < hMidpoint &&
                            rect.top + rect.height < hMidpoint);
        bool bottomQuadrant = (rect.top > hMidpoint);

        if (rect.left < vMidPoint &&
            rect.left + rect.width < vMidPoint) {
            if (topQuadrant) index = 1;
            else if (bottomQuadrant) index = 2;
        } else if (rect.left > vMidPoint) {
            if (topQuadrant) index = 0;
            else if (bottomQuadrant) index = 3;
        }

        return index;
    }

    int level;
    sf::FloatRect bounds;
    vector<pair<Entity, sf::FloatRect>> objects;
    unique_ptr<Quadtree> nodes[4];

public:
    Quadtree(int level, sf::FloatRect bounds) : level(level), bounds(bounds) {}

    void clear() {
        objects.clear();
        for (auto& node : nodes) {
            if (node) {
                node->clear();
            }
        }
    }

    void insert(Entity entity, sf::FloatRect rect) {
        if (nodes[0] != nullptr) {
            int index = getIndex(rect);
            if (index != -1) {
                nodes[index]->insert(entity, rect);
                return;
            }
        }

        objects.push_back({entity, rect});

        if (objects.size() > 4 && level < 5) {
            if (nodes[0] == nullptr) split();

            auto it = objects.begin();
            while (it != objects.end()) {
                int index = getIndex(it->second);
                if (index != -1) {
                    nodes[index]->insert(it->first, it->second);
                    it = objects.erase(it);
                } else {
                    ++it;
                }
            }
        }
    }

    vector<pair<Entity, sf::FloatRect>> retrieve(sf::FloatRect rect) {
        vector<pair<Entity, sf::FloatRect>> returnObjects;
        int index = getIndex(rect);

        if (index != -1 && nodes[0] != nullptr) {
            auto nodeObjects = nodes[index]->retrieve(rect);
            returnObjects.insert(returnObjects.end(), nodeObjects.begin(), nodeObjects.end());
        }

        returnObjects.insert(returnObjects.end(), objects.begin(), objects.end());
        return returnObjects;
    }
};

#endif //INDIVIDUALPLATFORMER_QUADTREE_H
