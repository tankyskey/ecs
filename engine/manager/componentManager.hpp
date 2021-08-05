#pragma once

#include <stdio.h>
#include <typeinfo>
#include <unordered_map>
#include "../utils/utils.hpp"
#include "../core/componentsArray.hpp"

class ComponentManager {
    private:
        std::unordered_map<const char*, IComponentsArray*> CPArrayMap;
        std::unordered_map<const char*, CPId_t> CPIdMap;
        CPId_t nextFreeId = 0;

    public:

        template <typename T>
        void registerComponent()
        {
            const char* name = typeid(T).name();

            //creer un nouvel array de component T
            CPArrayMap.insert({name, new ComponentsArray<T>()});
            CPIdMap.insert({name, nextFreeId});

            nextFreeId++;
        }

        template <typename T>
        CPId_t addComponent(Entity e, T component)
        {
            const char* name = typeid(T).name();
            getCPArray<T>(name)->addComponent(e, component) ;
            return CPIdMap[name];
        }

        template <typename T>
        CPId_t removeComponent(Entity e)
        {
            const char* name = typeid(T).name();
            getCPArray<T>( name )->removeComponent(e);
            return CPIdMap[name];
        }

        template <typename T>
        ComponentsArray<T>* getCPArray(const char* key)
        {
            return (ComponentsArray<T>*)CPArrayMap[key];
        }

        template <typename T>
        T& getComponent(Entity e)
        {
            return getCPArray<T>( typeid(T).name() )->getComponent(e);
        }

        void entityDestroyed(Entity e)
        {
            for(auto cparray: CPArrayMap)
                cparray.second->entityDestroyed( e );
        }

        template <typename T>
        CPId_t getComponentId()
        {
            return CPIdMap[typeid(T).name()];
        }
};

