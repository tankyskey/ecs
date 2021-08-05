#include "engine/engine.hpp"
#include "core.hpp"

#include "components/2d_core.hpp"
#include "system/renderSystem.hpp"
#include "system/eventSystem.hpp"
#include "system/physicSystem.hpp"
#include <thread>

Overseer overlord;
Core core;

void eventRoutine();
void renderRoutine();
void physicRoutine();

int main()
{
    core.init();
    core.createComponent();
    core.createSystems();

    core.createMap();

    std::thread renderThread (renderRoutine);
    std::thread physicThread (physicRoutine);

    eventRoutine(); // doit être dans le thread de core.init
    renderThread.join();
    physicThread.join();

    return 0;
}

void eventRoutine()
{
    double t0, t1, dt = 0;
    while(!core.systems.event->quit) {
        t0 = SDL_GetTicks();

        core.systems.event->update(dt);

        t1 = SDL_GetTicks();
        dt = t1 - t0;
    }
}

void renderRoutine()
{
    double t0, t1, dt = 0;
    while(!core.systems.event->quit) {
        t0 = SDL_GetTicks();

        core.systems.render->update(dt);

        t1 = SDL_GetTicks();
        dt = t1 - t0;
    }
}

void physicRoutine()
{
    double t0, t1, dt = 0;
    while(!core.systems.event->quit) {
        t0 = SDL_GetTicks();

        core.systems.physic->update(dt);

        t1 = SDL_GetTicks();
        dt = t1 - t0;
    }
}

