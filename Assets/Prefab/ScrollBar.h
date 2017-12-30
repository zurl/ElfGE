//
// Created by 张程易 on 18/12/2017.
//

#ifndef ELFGE_SCROLLBAR_H
#define ELFGE_SCROLLBAR_H

#include "GameEngine.h"
#include "UI/UI.h"

namespace Prefabs {

    class ScrollBar : public Prefab {

        class ScrollBarScript : public Component {
            double xl, xr, yl, yr, xsl, xsr;
            std::function<void(double)> *callback;
            std::function<void()> onenter, onexit;
            GameObject *unit;

        public:
            ScrollBarScript(double xl, double xr, double yl, double yr, double xsl, double xsr,
                            std::function<void(double)> *callback, GameObject *unit) : xl(xl), xr(xr), yl(yl), yr(yr),
                                                                                       xsl(xsl), xsr(xsr),
                                                                                       callback(callback), unit(unit) {}

            bool onPressed = false;
            double lastValue = 0.0f;


            void update() override {
                if (onPressed) {
                    double x = Utility::MOUSE_X - getGameObject()->transform.getLocalPosition().x;
                    if (x < xsl) x = xsl;
                    if (x > xsr) x = xsr;
                    double value = (x - xsl) / (xsr - xsl);
                    if (fabs(value - lastValue) >= 1e-2) {
                        lastValue = value;
                        callback->operator()(value);
                        unit->transform.setPosition(glm::vec3(
                                x,
                                unit->transform.getLocalPosition().y,
                                unit->transform.getLocalPosition().z
                        ));
                    }
                }
            }

            void onEnter() {
                onPressed = true;
                //unit->transform.setScale(glm::vec3(0.8));
            }

            void onExit() {
                onPressed = false;
                //unit->transform.setScale(glm::vec3(1.0));
            }

            void start() override {
                onenter = std::bind(&ScrollBarScript::onEnter, this);
                onexit = std::bind(&ScrollBarScript::onExit, this);

                Input::attachOnMouseClick(xl, xr, yl, yr, 10, &onenter, &onexit);

                Component::start();
            }

            void destroy() override {
                Input::detachOnMouseClick(&onenter);
                Component::destroy();
            }
        };

        GameObject *canvas;
        unsigned int backgroundImage;
        unsigned int foregroundImage;
        glm::vec3 position;
        glm::vec2 backgroundSize;
        glm::vec2 foregroundSize;
        std::function<void(double)> *callback;

    public:
        ScrollBar(GameObject *canvas, unsigned int backgroundImage, unsigned int foregroundImage,
                  const glm::vec3 &position, const glm::vec2 &backgroundSize, const glm::vec2 &foregroundSize,
                  std::function<void(double)> *callback) : canvas(canvas), backgroundImage(backgroundImage),
                                                           foregroundImage(foregroundImage), position(position),
                                                           backgroundSize(backgroundSize),
                                                           foregroundSize(foregroundSize), callback(callback) {}

        GameObject *instantiate(Scene *scene) override {
            auto result = scene->createGameObject();
            result->setParent(canvas);
            result->transform.setPosition(position);
            double px = result->transform.getLocalPosition().x;
            double py = result->transform.getLocalPosition().y;

            auto unit = scene->createGameObject();
            unit->setParent(result);
            unit->createComponent<Image>(foregroundImage, foregroundSize.x, foregroundSize.y);
            result->createComponent<ScrollBarScript>(
                    px - backgroundSize.x / 2, px + backgroundSize.x / 2,
                    py - backgroundSize.y / 2, py + backgroundSize.y / 2,
                    - backgroundSize.x / 2, backgroundSize.x / 2,
                    callback, unit
            );
            auto bg = scene->createGameObject();
            bg->setParent(result);
            bg->createComponent<Image>(backgroundImage, backgroundSize.x, backgroundSize.y);
            return result;
        }
    };
}

#endif //ELFGE_SCROLLBAR_H
