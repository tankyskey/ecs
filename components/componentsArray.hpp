#pragma once

#include <array>
#include <unordered_map>
#include <stdio.h>
#include <cassert>

#include "../utils/cst.hpp"

// [ C1 | C2 | C3 | C4 ] array
// [ 0  | 1  | 2  | 3  ] i2e
//  0:0  1:1  2:2  3:3   e2i
//
// [ C1 | C4 | C3 ]
// [ 0  | 3  | 2  ]
//  0:0  3:1  2:2

class IComponentsArray {
    public:
        virtual ~IComponentsArray() = default;
        virtual void entityDestroyed(int eId) = 0;
};

template <typename T>
class ComponentsArray: public IComponentsArray {
    private:
        std::array<T, MAX_ENTITY> array;
        std::unordered_map<int, int> e2i;
        int size;

    public:

        ComponentsArray(): size(0) {}

        void addComponent(int eId, T& component) {
            array[size] = component;
            e2i[eId] = size;
            // <=> e2i.insert({eId, size});

            size++;
        }

        void removeComponent(int eId) {
            int pos = e2i[eId],
                last = size -1;

            array[pos] = array[last];
            e2i.erase(eId);

            size--;
        }

        T& getComponent(int eId) {
            assert(e2i.find(eId) != nullptr && "entity dosent possess this type of component" );
            return array[ e2i[eId] ];
        }

        void entityDestroyed(int eId) override {
            removeComponent(eId);
        }
};
