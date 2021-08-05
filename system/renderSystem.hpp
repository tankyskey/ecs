#pragma once

#include <stdio.h>

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "../engine/engine.hpp"
#include "../components/2d_core.hpp"
#include "../core.hpp"

extern Overseer overlord;

class RenderSystem: public System {
    private:
        Entity playerId;

        inline bool onScreen(Renderable& renderable)
        {
            return  renderable.dst.x < width && renderable.dst.x + renderable.dst.w > 0 &&
                    renderable.dst.y < height && renderable.dst.y + renderable.dst.h > 0;
        }

    public:
        SDL_Renderer* renderer;
        SDL_Window* window;
        SDL_Rect viewPort;
        int width = 500,
            height = 500,
            maxFPS = 1000/60;

        void init(const char* title, int width, int height)
        {
            this->width = width;
            this->height = height;
            viewPort.w = width;
            viewPort.h = height;
            SDL_Init(SDL_INIT_VIDEO);

            window = SDL_CreateWindow(
                    title,
                    SDL_WINDOWPOS_UNDEFINED,
                    SDL_WINDOWPOS_UNDEFINED,
                    width,
                    height,
                    SDL_WINDOW_SHOWN
                    );

            renderer = SDL_CreateRenderer(
                    window,
                    -1,
                    SDL_RENDERER_ACCELERATED
                    );
        }

        void update(double dt)
        {
            double delay;
            SDL_RenderClear( renderer );

            viewPort.x = overlord.getComponent<Transform>( playerId ).position.x * 256;
            viewPort.y = overlord.getComponent<Transform>( playerId ).position.y * 128;

            for( Entity e: entities ) {
                auto& renderable = overlord.getComponent<Renderable>( e );
                auto& transform = overlord.getComponent<Transform>( e );

                renderable.dst.x = (int)transform.position.x * 256;
                renderable.dst.y = (int)transform.position.y * 128;

                renderable.dst.x -= viewPort.x;
                renderable.dst.y -= viewPort.y;

                if( e == playerId ) {
                    renderable.dst.x  += width / 4;
                    renderable.dst.y  += height / 4;
                }

                if( onScreen(renderable) )
                    SDL_RenderCopy( renderer, renderable.texture, &renderable.src, &renderable.dst);
            }

            SDL_RenderPresent( renderer );

            delay = maxFPS - dt;
            if( delay > 0)
                SDL_Delay(delay);
        }

        void setPlayerId(Entity playerId)
        {
            this->playerId = playerId;
        }
};
