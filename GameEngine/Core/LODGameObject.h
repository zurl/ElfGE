//
// Created by 张程易 on 25/12/2017.
//

#ifndef ELFGE_LODGAMEOBJECT_H
#define ELFGE_LODGAMEOBJECT_H


#include "GameObject.h"

class LODGameObject: public GameObject {
public:
    LODGameObject(const std::string &name);

    void update() override;

    void updateGraphics(RenderLayer renderLayer) override;
};


#endif //ELFGE_LODGAMEOBJECT_H
