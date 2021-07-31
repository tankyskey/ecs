#pragma once

#include <typeinfo>
#include <unordered_map>
#include "../system/system.hpp"

class SystemManager {
    private:
        std::unordered_map<const char*, System*> systemsMap;

    public:

        template <typename T>
        T* addSystem()
        {
            const char* name = typeid(T).name();
            T* system = new T;

            systemsMap.insert({name, system});

            return system;
        }

        template <typename T>
        T* getSystem() {
            return systemsMap[typeid(T).name()];
        }

        void entityDestroyed( Entity eId )
        {
            for(auto paire: systemsMap) {
                auto& system = paire.second;
                system->entities.erase( eId );
            }
        }

        template <typename S>
        void require(CPId_t cpId)
        {
            auto system = systemsMap[typeid(S).name()];
            system->signature.set(cpId, 1);
        }

        void entityChanged(Entity e, Signature signature)
        {
            for(auto paire: systemsMap) {
                auto& system = paire.second;

                if( (system->signature & signature) == system->signature)
                    system->entities.insert(e);
                else
                    system->entities.erase(e);
            }
        }
};
