#include <stdio.h>

// engine relative
#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>
#include "manager/overseer.hpp"


// user relative
#include "components/core.hpp"


Overseer overlord;

int main(){

    overlord.registerComponent<Transform>();
    overlord.registerComponent<Rigibody>();
    overlord.registerComponent<Player>();

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
                .velocity = Vect3(),
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

    auto r = overlord.getComponent<Transform>( id );
    printf("x: %f, y: %f, z: %f\n",
            r.position.x,
            r.position.y,
            r.position.z);

    auto r2 = overlord.getComponent<Rigibody>( id );
    printf("x: %f, y: %f, z: %f\n",
            r2.acceleration.x,
            r2.acceleration.y,
            r2.acceleration.z);

    overlord.destroyEntity(id);
    int id3 = overlord.createEntity();
    int id4 = overlord.createEntity();
    printf("id2: %d, id3: %d, id4: %d\n", id2, id3, id4);
    return 0;
}

