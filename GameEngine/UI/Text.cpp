//
// Created by 张程易 on 01/11/2017.
//

#include "Text.h"

void Text::start() {
    UIShader = ShaderManager::getShader("UI");
}


void Text::updateGraphics(RenderLayer renderLayer) {
    if (renderLayer == RenderLayer::SCREEN) {
        UIShader->setMat4("model", getGameObject()->getModelMatrix());
        UIShader->setVec3("color", fontColor);
        UIShader->setInt("mode", 0);
        fontFace->renderText(text);
    }
}

const std::string &Text::getText() const {
    return text;
}

void Text::setText(const std::string &text) {
    Text::text = text;
}

int Text::getFontSize() const {
    return fontSize;
}

void Text::setFontSize(int fontSize) {
    Text::fontSize = fontSize;
    getGameObject()->transform.setScale(glm::vec3(fontSize * 1.0f / fontFace->getFontSize()));
}

const glm::vec3 &Text::getFontColor() const {
    return fontColor;
}

void Text::setFontColor(const glm::vec3 &fontColor) {
    Text::fontColor = fontColor;
}

FontFace *Text::getFontFace() const {
    return fontFace;
}

void Text::setFontFace(FontFace *fontFace) {
    Text::fontFace = fontFace;
    getGameObject()->transform.setScale(glm::vec3(fontSize * 1.0f / fontFace->getFontSize()));
}

Text::Text(const std::string &text, FontFace *fontFace) : text(text), fontFace(fontFace) {}
