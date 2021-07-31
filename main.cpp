#include <stdio.h>
#include <iostream>

// engine relative
#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>
#include "engine.hpp"


// user relative
#include "components/core.hpp"
#include "system/physicSystem.hpp"


Overseer overlord;
template <typename T>
const char* type() {
    return typeid(T).name();
}

int main(){

    overlord.registerComponent<Transform>();
    overlord.registerComponent<Rigibody>();
    overlord.registerComponent<Player>();

    auto psys = overlord.addSystem<PhysicSystem>();
    overlord.require<PhysicSystem, Rigibody>();
    overlord.require<PhysicSystem, Transform>();

    int id = overlord.createEntity();
    int id2 = overlord.createEntity();


    overlord.addComponent<Transform>(id,
            Transform{
                .position = Vect3(1, 2, 3),
                .rotaion = Vect3(),
                .scale = Vect3()
            }
        );

    overlord.addComponent<Transform>(id2,
            Transform{
                .position = Vect3(3, 4, 5),
                .rotaion = Vect3(),
                .scale = Vect3()
            }
        );

    overlord.addComponent<Rigibody>(id,
            Rigibody{
                .velocity = Vect3(1, 0, 1),
                .acceleration = Vect3(5, 0, 7),
                .angularVelocity = Vect3(),
                .angularAcceleration = Vect3(),
                .mass = 0
            }
        );

    overlord.addComponent<Player>(id,
            Player{
            }
        );

    overlord.removeComponent<Transform>(id2);

    printf("id: %d, id2: %d\n", id, id2);

    auto& t = overlord.getComponent<Transform>( id );
    printf("x: %f, y: %f, z: %f\n",
            t.position.x,
            t.position.y,
            t.position.z);

    auto& r = overlord.getComponent<Rigibody>( id );
    printf("acc: \nx: %f, y: %f, z: %f\n",
            r.acceleration.x,
            r.acceleration.y,
            r.acceleration.z);

    psys->update(1);
    printf("x: %f, y: %f, z: %f\n",
            t.position.x,
            t.position.y,
            t.position.z);

    overlord.destroyEntity(id);
    int id3 = overlord.createEntity();
    int id4 = overlord.createEntity();
    printf("id2: %d, id3: %d, id4: %d\n", id2, id3, id4);

    printf("x: %f, y: %f, z: %f\n",
            t.position.x,
            t.position.y,
            t.position.z);

    psys->update(1);

    return 0;
}

