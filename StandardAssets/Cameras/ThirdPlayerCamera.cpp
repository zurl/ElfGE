//
// Created by 张程易 on 11/01/2018.
//

#include "ThirdPlayerCamera.h"

ThirdPlayerCamera::ThirdPlayerCamera(GameObject *Player, GameObject *Image) : Player(Player), Image(Image) {}

void ThirdPlayerCamera::update() {

    if (glfwGetKey(Utility::window, GLFW_KEY_F) == GLFW_PRESS) {
        if (delay > 5) {
            if (isAim) {
                zoom = 45.0f;
                Image->transform.translate(glm::vec3(10000, 0, 0));
            } else {
                zoom = 10.0f;
                Image->transform.translate(glm::vec3(-10000, 0, 0));
            }
            isAim = !isAim;
            delay = 0;
        }


    }
    delay++;

    float k = isAim ? 1.0f : -5.0f;
    getGameObject()->transform.setPosition(
            glm::vec3(Player->getWorldForward().x * k,
                      getGameObject()->getWorldForward().y * k + 2.0f,
                      Player->getWorldForward().z * k)
    );
}
