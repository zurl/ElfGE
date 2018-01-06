//
// Created by 张程易 on 18/12/2017.
//

#ifndef ELFGE_IMAGEBUTTON_H
#define ELFGE_IMAGEBUTTON_H

#include "GameEngine.h"
#include "UI/UI.h"

namespace Prefabs{
    class ImageButton : public Prefab {

        class ImageButtonScript : public Component {
            double xl, xr, yl, yr;
            std::function<void()> *callback, onenter, onexit;
        public:
            ImageButtonScript(double xl, double xr, double yl, double yr, std::function<void()> *callback) : xl(xl),
                                                                                                             xr(xr),
                                                                                                             yl(yl),
                                                                                                             yr(yr),
                                                                                                             callback(
                                                                                                                     callback) {}

            void onEnter() {
                if (callback != nullptr) callback->operator()();
                getGameObject()->transform.setScale(glm::vec3(0.8));
            }

            void onExit() {
                getGameObject()->transform.setScale(glm::vec3(1.0));
            }

            void start() override {
                onenter = std::bind(&ImageButtonScript::onEnter, this);
                onexit = std::bind(&ImageButtonScript::onExit, this);

                Input::attachOnMouseClick(xl, xr, yl, yr, 10, &onenter, &onexit);
                Component::start();
            }

            void sleep() override {
                printf("sleep");
                Input::detachOnMouseClick(&onenter);
            }

            void awake() override {
                printf("awake");
                Input::attachOnMouseClick(xl, xr, yl, yr, 10, &onenter, &onexit);
            }


            void destroy() override {
                Input::detachOnMouseClick(&onenter);
                Component::destroy();
            }
        };

        GameObject *canvas;
        unsigned int image;
        glm::vec2 size;
        glm::vec3 position;
        std::function<void()> *callback;

    public:
        ImageButton(GameObject *canvas, unsigned int image, const glm::vec2 &size, const glm::vec3 &position,
                    std::function<void()> *callback) : canvas(canvas), image(image), size(size), position(position),
                                                       callback(callback) {}

        GameObject *instantiate(Scene *scene) override {
            auto result = scene->createGameObject();
            result->setParent(canvas);
            result->transform.setPosition(position);
            double px = result->transform.getLocalPosition().x;
            double py = result->transform.getLocalPosition().y;
            result->createComponent<Image>(image, size.x, size.y);
            result->createComponent<ImageButtonScript>(
                    px - size.x / 2, px + size.x / 2,
                    py - size.y / 2, py + size.y / 2,
                    callback
            );
            return result;
        }
    };
}

#endif //ELFGE_IMAGEBUTTON_H
