//
// Created by 张程易 on 01/11/2017.
//

#ifndef ELFGE_TEXT_H
#define ELFGE_TEXT_H

#include <UI/Font/FontFace.h>
#include "GameEngine.h"

class Text: public Component {
    Shader * UIShader;
    std::string text;
    int fontSize;
    glm::vec3 fontColor;
    FontFace * fontFace;
public:

    Text(const std::string &text, FontFace *fontFace);

    void start() override;

    void updateGraphics(RenderLayer renderLayer) override;

    const std::string &getText() const;

    void setText(const std::string &text);

    int getFontSize() const;

    void setFontSize(int fontSize);

    const glm::vec3 &getFontColor() const;

    void setFontColor(const glm::vec3 &fontColor);

    FontFace *getFontFace() const;

    void setFontFace(FontFace *fontFace);
};


#endif //ELFGE_TEXT_H
