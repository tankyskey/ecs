#pragma once

#include "componentManager.hpp"
#include "entityManager.hpp"
#include "systemManager.hpp"

class Overseer {
    private:
        ComponentManager* componentManager = new ComponentManager;
        EntityManager* entityManager = new EntityManager;
        SystemManager* systemManager = new SystemManager;

    public:
        Overseer() {
        }

        // entity
        int createEntity() {
            return entityManager->createEntity();
        }

        void destroyEntity(int eId) {
            entityManager->destroyEntity( eId );
            componentManager->entityDestroyed( eId );
            systemManager->entityDestroyed( eId );
        }

        // component
        template <typename T>
        void registerComponent() {
            componentManager->registerComponent<T>();
        }

        template <typename T>
        void addComponent(int id, T cp) {
            componentManager->addComponent<T>(id, cp);
        }

        template <typename T>
        void removeComponent(int id) {
            componentManager->removeComponent<T>(id);
        }

        template <typename T>
        T& getComponent(int eId) {
            return componentManager->getComponent<T>(eId);
        }

        // system
        template <typename T>
        void registerSystem() {
            systemManager->addSystem<T>();
        }

};

