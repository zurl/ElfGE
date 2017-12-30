//
// Created by 张程易 on 01/11/2017.
//

#include "Canvas.h"

void Canvas::start() {
    UIShader = ShaderManager::getShader("UI");
}

void Canvas::update() {
    if (height != Utility::SCREEN_HEIGHT || width != Utility::SCREEN_WIDTH) {
        height = Utility::SCREEN_HEIGHT;
        width = Utility::SCREEN_WIDTH;
        projection = glm::ortho(0.0f, (float) width, 0.0f, (float) height);
    }
}

void Canvas::destroy() {

}

void Canvas::updateGraphics(RenderLayer renderLayer) {
    if (renderLayer != RenderLayer::SCREEN) return;
    UIShader->use();
    UIShader->setMat4("projection", projection);
}
