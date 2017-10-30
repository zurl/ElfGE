//
// Created by 张程易 on 29/10/2017.
//

#ifndef ELFGE_GAMEOBJECT_H
#define ELFGE_GAMEOBJECT_H
#include "Common.h"
#include "Transform.h"
#include "Component.h"

class GameObject {
private:
    std::list<Component *> components;
    GameObject * parent;
    std::list<GameObject *> children;
public:
    Transform transform;

    glm::mat4 getModelMatrix(){
        if(parent == nullptr) return transform.getModelMatrix(glm::mat4());
        else return transform.getModelMatrix(parent->getModelMatrix());
    }

    virtual void __update(){
        for(auto &x : components){
            x->update();
        }
    }

    template <typename T>
    T * getComponent(){
        for(auto & x: components){
            if(typeid(x) == typeid(T*)){
                return dynamic_cast<T*>(x);
            }
        }
        throw Exception("Component does not exists");
    }

    template <typename T>
    GameObject * addComponent(
            T * component,
            typename std::enable_if<std::is_base_of<Component, T>::value>::type* = 0
    ){
        components.push_back(component);
        return this;
    }

    template<typename T, typename... Args>
    GameObject * createComponent(Args&&... args){
        return addComponent(new T(std::forward<Args>(args)...));
    };

    GameObject *getParent() const {
        return parent;
    }

    void setParent(GameObject *parent) {
        if( parent == this->parent ) return;
        if( parent != nullptr ){
            parent->__detachChildren(this);
        }
        this->parent = parent;
        this->parent->__attachChildren(this);
    }

    void __attachChildren(GameObject * gameObject){
        children.emplace_back(gameObject);
    }

    void __detachChildren(GameObject * gameObject){
        children.remove(gameObject);
    }

    void __detachComponent(Component * component){
        components.remove(component);
    }

    static void destroy(GameObject * gameObject){
        if(gameObject->parent != nullptr){
            gameObject->parent->__detachChildren(gameObject);
        }
        while(!gameObject->children.empty()){
            destroy(gameObject->children.front());
        }
        delete gameObject;
    }

    static void destroy(Component * component){
        if(component->getParent() != nullptr){
            component->getParent()->__detachComponent(component);
        }
        delete component;
    }
};


#endif //ELFGE_GAMEOBJECT_H
