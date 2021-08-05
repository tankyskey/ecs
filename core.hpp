#pragma once
#include "engine/engine.hpp"

#include "components/2d_core.hpp"
#include "system/renderSystem.hpp"
#include "system/eventSystem.hpp"
#include "system/physicSystem.hpp"

class Core {
    private:
        int mapW, mapH;

    public:
        struct {
            RenderSystem* render;
            EventSystem* event;
            PhysicSystem* physic;
        } systems;
        Entity playerId;

        void init();
        void createSystems();
        void createComponent();

        Renderable createRenderable(const char* path, int x, int y, int src_w, int src_h, int dst_w, int dst_h);
        Renderable createRenderable(const char* path, int x, int y, int src_w, int src_h);

        Entity createObject(const char* path, int w, int h, double x, double y);

        void helloWorld();
        void createMap();
};

