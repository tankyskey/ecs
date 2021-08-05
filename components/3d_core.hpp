#pragma once
#include "../engine/engine.hpp"
#include "../engine/math/vect3.hpp"
#include <SDL2/SDL.h>

struct Rigibody {
    Vect3 velocity;
    Vect3 acceleration;

    Vect3 angularVelocity;
    Vect3 angularAcceleration;
};

struct Transform {
    Vect3 position;
    Vect3 rotaion;
    Vect3 dimension;
};

struct Renderable {
    SDL_Texture* texture;
    SDL_Rect dst;
    SDL_Rect src;
    int layer;
};

