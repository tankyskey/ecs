#include "core.hpp"

void Core::init()
{
    mapW = 10;
    mapH = 10;
}

void Core::createSystems()
{
    systems.render = overlord.addSystem<RenderSystem>();
    overlord.require<RenderSystem, Renderable>();
    overlord.require<RenderSystem, Transform>();
    systems.render->init("Engine", 1000, 1000);

    systems.event = overlord.addSystem<EventSystem>();
    overlord.require<EventSystem, Player>();
    systems.event->init();

    systems.physic = overlord.addSystem<PhysicSystem>();
    overlord.require<PhysicSystem, Rigibody>();
    overlord.require<PhysicSystem, Transform>();
    systems.physic->init();
}

void Core::createComponent()
{
    overlord.registerComponent<Transform>();
    overlord.registerComponent<Renderable>();
    overlord.registerComponent<Player>();
    overlord.registerComponent<Rigibody>();
}


Renderable Core::createRenderable(const char* path, int x, int y, int src_w, int src_h, int dst_w, int dst_h)
{
    SDL_Surface* surf = IMG_Load(path);
    SDL_Texture* texture = SDL_CreateTextureFromSurface(systems.render->renderer, surf);
    SDL_Rect src = {0, 0, src_w, src_h};
    SDL_Rect dst = {x, y, dst_w, dst_h};
    Renderable r = {
        .texture = texture,
        .dst = dst,
        .src = src,
        .layer = 0
    };

    return r;
}

Renderable Core::createRenderable(const char* path, int x, int y, int src_w, int src_h)
{
    return createRenderable(path, x, y, src_w, src_h, src_w, src_h);
}

Entity Core::createObject(const char* path, int w, int h, double x, double y)
{
    Entity id = overlord.createEntity();

    auto r = createRenderable(path, 0, 0, w, h, 512, 512);
    overlord.addComponent<Renderable>(id, r);
    overlord.addComponent<Transform>(id,
            Transform{
                .position = {x, y},
                .rotation = {},
                .dimension = {}
            });

    return id;
}

void Core::helloWorld()
{
    createObject("res/grassyGround.png", 512, 512, 0, 0);
    createObject("res/grassyGround.png", 512, 512, 256, 128);

    Entity player = createObject("res/tanks.png", 1024, 1024, 0, 0);
    createObject("res/usine.png", 1024, 1024, 0, 0);

    overlord.addComponent<Player>(player, Player{});
    overlord.addComponent<Rigibody>(player, Rigibody{});
}

void Core::createMap()
{
    for(int i=0; i<mapH; i++){
        for(int j=0; j<mapW; j++){
            Entity id = createObject("res/grassyGround.png", 512, 512, i-j, j+i);
            overlord.getComponent<Renderable>(id).isGround = true;
        }
    }
    createObject("res/usine.png", 1024, 1024, 0, 0);
    createObject("res/usine.png", 1024, 1024, 2, 2);

    playerId = createObject("res/tanks.png", 1024, 1024, 0, 0);
    overlord.addComponent<Player>(playerId, Player{});
    overlord.addComponent<Rigibody>(playerId, Rigibody{});

    systems.render->setPlayerId( playerId );

    //Entity ennemy1 = createObject("res/tanks.png", 1024, 1024, 0, 0);
}
