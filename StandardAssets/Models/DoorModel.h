//
// Created by sky on 2018/1/3.
//

#ifndef ELFGE_DOORMODEL_H
#define ELFGE_DOORMODEL_H


#include <Physics/Colliders/AABBCollider.h>
#include "DefaultModel.h"

class DoorModel : public DefaultModel{
    bool stopped = false,direction = true; // direction true for opening, false for closing;
    double angularSpeed = 2.0f,rotationAngle=0,openAngle = 2.0f;
public:
    DoorModel(const std::string &path):DefaultModel(path){}
    void openDoor(){
        if(!stopped) return;
        direction = true;
        stopped = false;
        getGameObject()->getComponent<AABBCollider>()->setWall(false);
    }
    void closeDoor(){
        if(!stopped) return;
        direction = false;
        stopped = false;
        getGameObject()->getComponent<AABBCollider>()->setWall(true);
    }
    void update(){
        static double rot;
        if(!stopped){
            rot = angularSpeed*Utility::deltaTime;
            if(direction){
                rotationAngle+=rot;
                if(rotationAngle>=openAngle) stopped = true;
            }
            else{
                rotationAngle-=rot;
                if(rotationAngle<=0) stopped = true;
                rot*=-1;
            }
            getGameObject()->transform.rotate(glm::vec3(0,1,0),rot);
        }
    }
};


#endif //ELFGE_DOORMODEL_H
