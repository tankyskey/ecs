#pragma once

#include <SDL2/SDL.h>
#include <map>
#include <list>
#include <iostream>
#include "../engine/engine.hpp"
#include "../components/2d_core.hpp"

extern Overseer overlord;
using pfun = void (*)(SDL_Keysym);

class EventSystem: public System {
    private:

        char moving = 0;
        double xspeed = 0.2,
               yspeed = 0.1;

        std::map<SDL_Keycode, pfun> actionMap;
        std::list<SDL_Keycode> downKey;

        void move(SDL_KeyCode key)
        {
            auto& rigibody = overlord.getComponent<Rigibody>( *entities.begin() );
            auto& renderable = overlord.getComponent<Renderable>( *entities.begin() );

            switch(key) {
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

                default:
                    break;
            }
        }

        void stopMove(SDL_KeyCode key)
        {
            auto& rigibody = overlord.getComponent<Rigibody>( *entities.begin() );

            switch(key) {
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

                default:
                    break;
            }

            if( !moving ) {
                rigibody.velocity.y = 0;
                rigibody.velocity.x = 0;
            }
        }

    public:
        bool quit = false;

        void init()
        {
        }

        bool onKeyPress(SDL_Keycode key, pfun fun, bool ignoreHolding=false)
        {
            return (actionMap[key] = fun) != 0;
        }

        bool onKeyRelease(SDL_Keycode key, pfun fun)
        {
            return (actionMap[key] = fun) != 0;
        }

        void update(double dt)
        {
            SDL_Event e = {0};
            while( SDL_PollEvent(&e) ) {
                switch(e.type) {
                    case SDL_QUIT:
                        quit = true;
                        break;

                    case SDL_KEYDOWN:
                        downKey.push_back(e.key.keysym.sym);
                        keyDownEvent(e);
                        break;

                    case SDL_KEYUP:
                        downKey.remove(e.key.keysym.sym);
                        keyUpEvent(e);
                        break;

                    default:
                        break;
                }
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

