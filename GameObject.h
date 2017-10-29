//
// Created by 张程易 on 29/10/2017.
//

#ifndef ELFGE_GAMEOBJECT_H
#define ELFGE_GAMEOBJECT_H
#include "Common.h"
#include "Component.h"

class GameObject {
private:
    std::list<Component *> componentsList;
    GameObject * parent;
    std::list<GameObject *> children;
public:
    virtual void __update(){
        for(auto &x : componentsList){
            x->update();
        }
    }

    template <typename T>
    T getComponent(){
        for(auto & x: componentsList){
            if(typeid(x) == typeid(T)){
                return x;
            }
        }
    }

    template <typename T>
    T * addComponent(
            T * component,
            typename std::enable_if<std::is_base_of<Component, T>::value>::type* = 0
    ){
        componentsList.push_back(component);
        return component;
    }
};


#endif //ELFGE_GAMEOBJECT_H
