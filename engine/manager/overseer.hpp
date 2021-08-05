#pragma once

#include "componentManager.hpp"
#include "entityManager.hpp"
#include "systemManager.hpp"

#include "../utils/utils.hpp"

#include <vector>

class Overseer {
    private:
        ComponentManager* componentManager = new ComponentManager;
        EntityManager* entityManager = new EntityManager;
        SystemManager* systemManager = new SystemManager;

    public:

        // entity
        int createEntity()
        {
            return entityManager->createEntity();
        }

        void destroyEntity(Entity eId)
        {
            entityManager->destroyEntity( eId );
            componentManager->entityDestroyed( eId );
            systemManager->entityDestroyed( eId );
        }

        // entity/component
        template <typename T>
        void addComponent(Entity e, T cp)
        {
            CPId_t id = componentManager->addComponent<T>(e, cp);
            Signature s = entityManager->addComponent(e, id);
            systemManager->entityChanged(e, s);
        }

        template <typename T>
        void removeComponent(Entity eId)
        {
            Signature s = componentManager->removeComponent<T>(eId);
            systemManager->entityChanged(eId, s);
        }

        template <typename T>
        T& getComponent(Entity eId)
        {
            return componentManager->getComponent<T>(eId);
        }

        // component
        template <typename T>
        void registerComponent()
        {
            componentManager->registerComponent<T>();
        }

        // system
        template <typename T>
        T* addSystem()
        {
            return systemManager->addSystem<T>();
        }

        template <typename S, typename C>
        void require()
        {
            systemManager->require<S>( getComponentId<C>() );
        }

        template <typename T>
        CPId_t getComponentId()
        {
            return componentManager->getComponentId<T>();
        }
};

