#pragma once
#include "../utils/utils.hpp"

struct Rigibody {
    Vect3 velocity;
    Vect3 acceleration;
    Vect3 angularVelocity;
    Vect3 angularAcceleration;
    int mass;
};

struct Transform {
    Vect3 position;
    Vect3 rotaion;
    Vect3 scale;
};

struct Solid {
    // collision (hitbox)
    // shape (rect, sphere, dot, circle, etc)
};

struct Damageable {
    int Health;
};

struct Renderable {
};

struct Player {
};
