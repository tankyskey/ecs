#pragma once

#include "system.hpp"
#include "../components/core.hpp"
#include "../manager/overseer.hpp"

extern Overseer overlord;

class PhysicSystem: public System {
    public:

        void init()
        {
            // pour toutes les entites existante e:
            //  si signature(e) == this->signature:
            //   this->entities.add( e );
        }

        void update(double dt)
        {
            double half_dt_square = dt * dt * 0.5;

            for( int e: entities ) {
                auto& r = overlord.getComponent<Rigibody>( e );
                auto& t = overlord.getComponent<Transform>( e );


                t.position += r.velocity * dt;

                r.velocity += r.acceleration * dt;
            }
        }
};
