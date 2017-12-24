//
// Created by 张程易 on 24/12/2017.
//

#ifndef ELFGE_PLAINTEXT_H
#define ELFGE_PLAINTEXT_H

#include "GameEngine.h"
#include "UI/UI.h"

namespace Prefabs {
    class PlainText : public Prefab{
        GameObject * canvas;
        FontFace * font;
        std::string text;
        glm::vec3 pos;
        float size;
    public:
        PlainText(GameObject *canvas, FontFace *font, const std::string &text, const glm::vec3 &pos, float size)
                : canvas(canvas), font(font), text(text), pos(pos), size(size) {}

        GameObject *instantiate(Scene *scene) override {
            auto text2 = scene
                    ->createGameObject()
                    ->createComponent<Text>(text, font);

            text2->setParent(canvas);
            text2->transform.translate(pos);
            text2->transform.setScale(glm::vec3(size));
            return text2;
        }
    };
}


#endif //ELFGE_PLAINTEXT_H
