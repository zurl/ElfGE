//
// Created by 张程易 on 30/10/2017.
//

#ifndef ELFGE_GAMESCRIPT_H
#define ELFGE_GAMESCRIPT_H

#include "../Core/Component.h"
#include "../Core/Input.h"


class GameScript: public Component {
    std::function<void(double, double)> mouseHandler;
    std::function<void(double)> scrollHandler;
protected:
    void enableMouseInput();
    void enableScrollInput();
public:
    virtual void onMouseMove(double x, double y){ }
    virtual void onScrollMove(double x){ }
    void destroy() override;
};


#endif //ELFGE_GAMESCRIPT_H
