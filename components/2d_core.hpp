#pragma once
#include "../engine/engine.hpp"
#include "../engine/math/vect2.hpp"
#include <SDL2/SDL.h>

// ============ BASE
struct Rigibody {
    Vect2 velocity;
    Vect2 acceleration;
};

struct Transform {
    Vect2 position;
    Vect2 rotation;
    Vect2 dimension;
};

struct Renderable {
    SDL_Texture* texture;
    SDL_Rect dst;
    SDL_Rect src;
    int layer;
    bool isGround = false;
};

struct Player {
};
// ============


// ============ INDIVIDUAL
struct Damageable {
    int health;
};

struct Unit {
    int actionPoint;
};
// ============


// ============ COMMON
struct UnitType {
    int mvtRadius;
    int attRadius;
    int attValue;
    int defValue;
};

struct Factory {
    const char* product;
    double productionTime;
};

struct Building {
};
// ============


// ============ COMMON / INDIVIDUAL
struct AI {
};
// ============
