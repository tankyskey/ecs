#pragma once
#include "../utils/utils.hpp"

struct Rigibody {
    vect3 velocity;
    vect3 acceleration;
    vect3 angularVelocity;
    vect3 angularAcceleration;
    vect3 mass;
};

struct Transform {
    vect3 position;
    vect3 rotaion;
    vect3 scale;
};

struct Damageable {
    int Health;
};

struct Renderable {
};

struct Player {
};
