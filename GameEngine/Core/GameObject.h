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
    GameObject *parent = nullptr;
    std::list<GameObject *> children;
    std::string name;

    int status = 0;

    void attachChildren(GameObject *gameObject);

    void detachChildren(GameObject *gameObject);

    void detachComponent(Component *component);

public:

    GameObject(const std::string &name);

    Transform transform;

    glm::mat4 getModelMatrix();

    glm::vec3 getWorldPosition() const;

    glm::quat getWorldQuaternion() const;

    glm::vec3 getWorldScale() const;

    glm::vec3 getWorldForward() const;

    glm::vec3 getWorldUp() const;

    glm::vec3 getWorldRight() const;

    glm::vec3 getWorldRotation() const;

    virtual void start();

    virtual void update();

    virtual void destroy();

    virtual void sleep();

    virtual void awake();

    virtual void updateGraphics(RenderLayer renderLayer);

    template<typename T>
    T *getComponent(
            typename std::enable_if<std::is_base_of<Component, T>::value>::type * = 0
    ) {
        for (auto &x: components) {
            auto ptr = dynamic_cast<T *>(x);
            if (ptr != nullptr) return ptr;
        }
        return nullptr;
    }

    template<typename T>
    std::vector<T *> getComponents(
            typename std::enable_if<std::is_base_of<Component, T>::value>::type * = 0
    ) {
        std::vector<T *> result;
        for (auto &x: components) {
            auto ptr = dynamic_cast<T *>(x);
            if (ptr != nullptr) result.emplace_back(ptr);
        }
        return result;
    }


    template<typename T>
    GameObject *addComponent(
            T *component,
            typename std::enable_if<std::is_base_of<Component, T>::value>::type * = 0
    ) {
        components.push_back(component);
        component->setGameObject(this);
        return this;
    }

    template<typename T>
    void removeComponent(
            typename std::enable_if<std::is_base_of<Component, T>::value>::type * = 0
    ) {
        for (auto &x: components) {
            auto ptr = dynamic_cast<T *>(x);
            if (ptr != nullptr) {
                x->destroy();
                delete x;
                components.remove(x);
            }
        }
    }

    template<typename T, typename... Args>
    GameObject *createComponent(Args &&... args) {
        return addComponent(new T(std::forward<Args>(args)...));
    };

    GameObject *getParent() const {
        return parent;
    }

    void setParent(GameObject *parent);

    static void destroy(GameObject *gameObject);

    static void destroy(Component *component);

    virtual ~GameObject();

    const std::string &getName() const;

    void setName(const std::string &name);

    const std::list<GameObject *> &getChildren() const;

    const std::list<Component *> &getComponents() const;

    int getStatus() const;

    void setStatus(int status);

};


#endif //ELFGE_GAMEOBJECT_H
