#pragma once

#include <set>
#include "../utils/utils.hpp"

class System {
    public:
        std::set<Entity> entities;
        Signature signature;
};
