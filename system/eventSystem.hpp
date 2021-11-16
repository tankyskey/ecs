#pragma once

#include <SDL2/SDL.h>
#include "../engine/engine.hpp"
#include "../components/2d_core.hpp"

extern Overseer overlord;

class EventSystem: public System {
    private:
        char moving = 0;
        double xspeed = 0.2,
               yspeed = 0.1;

    public:
        bool quit = false;

        void init()
        {}

        void update(double dt)
        {
            SDL_Event e = {0};
            SDL_WaitEvent(&e);
            switch(e.type) {
                case SDL_QUIT:
                    quit = true;
                    break;

                case SDL_KEYDOWN:
                    keyDownEvent(e);
                    break;

                case SDL_KEYUP:
                    keyUpEvent(e);
                    break;

                default:
                    break;
            }

        }

    private:
        void keyDownEvent(SDL_Event& e)
        {
            auto& rigibody = overlord.getComponent<Rigibody>( *entities.begin() );
            auto& renderable = overlord.getComponent<Renderable>( *entities.begin() );

            switch(e.key.keysym.sym) {
                case SDLK_z:
                    rigibody.velocity.x = xspeed;
                    rigibody.velocity.y = -yspeed;
                    renderable.src.x = 0;
                    moving |= 0x1;
                    break;

                case SDLK_q:
                    rigibody.velocity.x = -xspeed;
                    rigibody.velocity.y = -yspeed;
                    renderable.src.x = 1024;
                    moving |= 0x2;
                    break;

                case SDLK_s:
                    rigibody.velocity.x = -xspeed;
                    rigibody.velocity.y = yspeed;
                    renderable.src.x = 2048;
                    moving |= 0x4;
                    break;

                case SDLK_d:
                    rigibody.velocity.x = xspeed;
                    rigibody.velocity.y = yspeed;
                    renderable.src.x = 3072;
                    moving |= 0x8;
                    break;

                case SDLK_SPACE:
                    break;

                case SDLK_ESCAPE:
                    quit = true;
                    break;
            }
        }

        void keyUpEvent(SDL_Event& e)
        {
            auto& rigibody = overlord.getComponent<Rigibody>( *entities.begin() );

            switch(e.key.keysym.sym) {
                case SDLK_z:
                    moving &= 0xe;
                    break;
                case SDLK_q:
                    moving &= 0xd;
                    break;
                case SDLK_s:
                    moving &= 0xb;
                    break;
                case SDLK_d:
                    moving &= 0x7;
                    break;

                case SDLK_SPACE:
                    break;

                case SDLK_ESCAPE:
                    break;
            }

            if( !moving ) {
                    rigibody.velocity.y = 0;
                    rigibody.velocity.x = 0;
            }
        }
};

