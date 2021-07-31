#pragma once

#include "../utils/cst.hpp"
#include <array>

class EntityManager {
    private:
        std::array<int, MAX_ENTITY> availableId;
        int size;
        int nextId;

    public:
        EntityManager(): size(0), nextId(0)
        {
        }

        /// @return: new entity id
        int createEntity()
        {
            if( size == 0 )
                return nextId++;

            int id = availableId[0];
            size--;
            availableId[0] = availableId[size];
            return id;
        }

        void destroyEntity(int id)
        {
            availableId[size++] = id;
        }
};
