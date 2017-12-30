//
// Created by 张程易 on 27/12/2017.
//

#ifndef ELFGE_CHARACTERCONTROLLER_H
#define ELFGE_CHARACTERCONTROLLER_H


#include "GameEngine.h"
#include "RigidBody.h"

class CharacterController: public GameScript {

    float mouseSensitivity;

    float speed;

    RigidBody * rigidBody;

public:

    CharacterController(float mouseSensitivity = 0.002f, float speed = 0.05f);

    void start() override;

    void update() override;

    void onMouseMove(double x, double y) override;

};


#endif //ELFGE_CHARACTERCONTROLLER_H
