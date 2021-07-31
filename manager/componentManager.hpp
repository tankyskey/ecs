#pragma once
#include "../utils/utils.hpp"

#include <typeinfo>
#include <unordered_map>
#include "../components/componentsArray.hpp"
#include <stdio.h>

class ComponentManager {
    private:
        int componentCount = 0;
        std::unordered_map<const char*, IComponentsArray*> CPArrayMap;

    public:
        ComponentManager()
        {
        }

        template <typename T>
        void registerComponent()
        {
            const char* name = typeid(T).name();

            //creer un nouvel array de component T
            CPArrayMap.insert({name, new ComponentsArray<T>()});

            componentCount++;
            printf("%s, registered\n", name);
        }

        template <typename T>
        void addComponent(int eId, T component)
        {
            const char* name = typeid(T).name();

            //((ComponentsArray<T>*)CPArrayMap[name])->addComponent(eId, component);
            getCPArray<T>(name)->addComponent(eId, component) ;
        }

        template <typename T>
        ComponentsArray<T>* getCPArray(const char* key)
        {
            return (ComponentsArray<T>*)CPArrayMap[key];
        }

        template <typename T>
        void removeComponent(int eId)
        {
            getCPArray<T>( typeid(T).name() )->removeComponent(eId);
        }

        template <typename T>
        T& getComponent(int eId)
        {
            return getCPArray<T>( typeid(T).name() )->getComponent(eId);
        }

        void entityDestroyed(int eId)
        {
            for(auto cparray: CPArrayMap)
                cparray.second->entityDestroyed( eId );
        }
};

