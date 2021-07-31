#pragma once

#include <typeinfo>
#include "../system/systemCore.hpp"
#include <unordered_map>

class SystemManager {
    private:
        std::unordered_map<const char*, System*> systemsMap;

    public:
        SystemManager() {
        }

        template <typename T>
        T* addSystem() {
            const char* name = typeid(T).name();
            T* system = new T;

            systemsMap.insert({name, system});

            return system;
        }

        void entityDestroyed( int eId ) {
        }
};
