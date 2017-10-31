//
// Created by 张程易 on 29/10/2017.
//

#ifndef ELFGE_GAMEOBJECT_H
#define ELFGE_GAMEOBJECT_H
#include "../Common.h"
#include "Transform.h"
#include "Component.h"

class GameObject {
private:
    std::list<Component *> components;
    GameObject * parent;
    std::list<GameObject *> children;

    void attachChildren(GameObject * gameObject);

    void detachChildren(GameObject * gameObject);

    void detachComponent(Component * component);
public:
    Transform transform;

    glm::mat4 getModelMatrix(){
        if(parent == nullptr) return transform.getModelMatrix(glm::mat4(1.0f));
        else return transform.getModelMatrix(parent->getModelMatrix());
    }

    virtual void start(){
        for(auto &x : components){
            x->start();
        }
        for(auto &x : children){
            x->start();
        }
    }

    virtual void update(){
        for(auto &x : components){
            x->update();
        }
        for(auto &x : children){
            x->update();
        }
    }

    virtual void destroy(){
        for(auto &x : components){
            x->destroy();
            detachComponent(x);
        }
        for(auto &x : children){
            x->destroy();
        }
        if(parent != nullptr){
            parent->detachChildren(this);
        }
    }

    template <typename T>
    T * getComponent(
            typename std::enable_if<std::is_base_of<Component, T>::value>::type* = 0
    ) {
        for(auto & x: components){
            auto ptr = dynamic_cast<T*>(x);
            if(ptr != nullptr) return ptr;
        }
        throw Exception("Component does not exists");
    }


    template <typename T>
    GameObject * addComponent(
            T * component,
            typename std::enable_if<std::is_base_of<Component, T>::value>::type* = 0
    ){
        components.push_back(component);
        component->setGameObject(this);
        return this;
    }

    template<typename T, typename... Args>
    GameObject * createComponent(Args&&... args){
        return addComponent(new T(std::forward<Args>(args)...));
    };

    GameObject *getParent() const {
        return parent;
    }

    void setParent(GameObject *parent);

    static void destroy(GameObject * gameObject){
        gameObject->destroy();
        delete gameObject;
    }

    static void destroy(Component * component){
        component->destroy();
        delete component;
    }

    virtual ~GameObject();

};


#endif //ELFGE_GAMEOBJECT_H
