//
// Created by lulufa on 2017/12/26.
//

#ifndef ELFGE_REALCAMERA_H
#define ELFGE_REALCAMERA_H

#include "StandardAssets.h"

class RealCamera : public FirstPlayerCamera{
public:
    GameObject * Player;
    GameObject * Image;
    GameObject * fuck;
    void setPlayerImage(GameObject * player, GameObject * image){
        Player = player;
        Image = image;
    }

    void start() override {
        fuck = instantiate<Prefabs::Cube>(glm::vec3(0));
        DefaultCamera::start();
    }


    void update() override{


        static bool isAim = false;
        static int delay = 0;
        if (glfwGetKey(Utility::window, GLFW_KEY_F) == GLFW_PRESS){
            if(delay > 5){
                if(isAim){
                    zoom = 45.0f;
                    //getGameObject()->transform.translate(-Player->transform.getForward() * 10.0f);
                    Image->transform.translate(glm::vec3(10000,0,0));
                }
                else{
                    zoom = 10.0f;
                    //getGameObject()->transform.translate(Player->transform.getForward() * 1.0f);
                    Image->transform.translate(glm::vec3(-10000,0,0));
                }
                isAim = !isAim;
                delay=0;
            }


        }
        delay++;
        static float lastY = 0;
        if (glfwGetKey(Utility::window, GLFW_KEY_K) == GLFW_PRESS) {
            printf("%f %f %f %f %f\n", axisUp, lastY,
                   Player->transform.getLocalRight().x, Player->transform.getLocalRight().y,
                   Player->transform.getLocalRight().z);
        }
        if(fabs(axisUp - lastY) > 1e-3) {
            Player->transform.rotate(Transform::up, axisUp - lastY);
            lastY = axisUp;
        }
        //Player->transform.rotate(glm::vec3(0,1,0), 0.001f);

//        if(isAim)
//            getGameObject()->transform.setPosition(glm::vec3(Player->transform.getLocalPosition().x + Player->transform.getLocalRight().x * 1.0f,
//                                                             Player->transform.getLocalPosition().y + 4.0f,
//                                                             Player->transform.getLocalPosition().z + Player->transform.getLocalRight().z * 1.0f)
//            );
//        else

        getGameObject()->transform.setPosition(glm::vec3(Player->transform.getLocalPosition().x - Player->transform.getLocalRight().x * 15.0f,
                                                         Player->transform.getLocalPosition().y - Player->transform.getLocalRight().y * 15.0f + 4.0f,
                                                         Player->transform.getLocalPosition().z - Player->transform.getLocalRight().z * 15.0f)
        );

    }


};



#endif //ELFGE_REALCAMERA_H
