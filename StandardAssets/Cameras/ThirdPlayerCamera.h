//
// Created by 张程易 on 11/01/2018.
//

#ifndef ELFGE_THIRDPLAYERCAMERA_H
#define ELFGE_THIRDPLAYERCAMERA_H

#include "GameEngine.h"
#include "FirstPlayerCamera.h"

class ThirdPlayerCamera : public FirstPlayerCamera {
public:
    GameObject *Player;
    GameObject *Image;
    bool isAim = false;
    int delay = 0;

    ThirdPlayerCamera(GameObject *Player, GameObject *Image);


    void update() override;

};


#endif //ELFGE_THIRDPLAYERCAMERA_H
