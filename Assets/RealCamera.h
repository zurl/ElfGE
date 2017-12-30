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
    void setPlayerImage(GameObject * player, GameObject * image){
        Player = player;
        Image = image;
    }


    void update() override {


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

        if(isAim)
            getGameObject()->transform.setPosition(glm::vec3(Player->transform.getPosition().x + Player->transform.getRight().x * 1.0f,
                                                             Player->transform.getPosition().y + getGameObject()->transform.getForward().y * 1.0f + 2.0f,
                                                             Player->transform.getPosition().z + Player->transform.getRight().z * 1.0f)
            );
        else

            getGameObject()->transform.setPosition(glm::vec3(Player->transform.getPosition().x - Player->transform.getRight().x * 5.0f,
                                                             Player->transform.getPosition().y - getGameObject()->transform.getForward().y * 5.0f + 2.0f,
                                                             Player->transform.getPosition().z - Player->transform.getRight().z * 5.0f)
            );
        static float lastY = glm::pi<float>();
        //printf("%f\n", camera->transform.getRotation().y - lastY);
        Player->transform.rotate(glm::vec3(0,1,0), getGameObject()->transform.getRotation().y - lastY );
        lastY = getGameObject()->transform.getRotation().y;

    }


};



#endif //ELFGE_REALCAMERA_H
