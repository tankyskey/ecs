#pragma once

#include "../utils/utils.hpp"
#include <queue>
#include <unordered_map>

class EntityManager {
    private:
        std::queue<Entity> availableId;

        int nextId;

        std::unordered_map<Entity, Signature> signatures;

    public:
        EntityManager(): nextId(0)
        {
        }

        Entity createEntity()
        {
            Entity id;

            if( availableId.empty() ) {
                id = nextId++;
            }
            else {
                id = availableId.front();
                availableId.pop();
            }

            signatures[id].reset();
            return id;
        }

        void destroyEntity(Entity e)
        {
            availableId.push(e);
            signatures[e].reset();
        }

        Signature getSignature(Entity e)
        {
            return signatures[e];
        }

        Signature addComponent(Entity e, CPId_t id)
        {
            signatures[e].set(id, 1);
            return signatures[e];
        }

        Signature removeComponent(Entity e, CPId_t id)
        {
            signatures[e].set(id, 0);
            return signatures[e];
        }

};
