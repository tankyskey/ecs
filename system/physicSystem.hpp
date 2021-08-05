#pragma once

#include "../engine/engine.hpp"
#include "../components/2d_core.hpp"

extern Overseer overlord;

class PhysicSystem: public System {
    private:
    public:

        void init()
        {
        }

        void update(double dt)
        {
            double delay;

            for(auto eId: entities) {
                auto& rigibody = overlord.getComponent<Rigibody>(eId);
                auto& transform = overlord.getComponent<Transform>(eId);

                transform.position += rigibody.velocity * dt;

                rigibody.velocity += rigibody.acceleration * dt;
            }

            delay = 1000/60 - dt;
            if( delay > 0)
                SDL_Delay(delay);
        }
};
