//
// Created by 张程易 on 30/12/2017.
//

#include "ParticleFactory.h"


void ParticleFactory::updateGraphics(RenderLayer renderLayer) {
    if( renderLayer != RenderLayer::WORLD) return;

    glDepthMask(GL_FALSE);
    glBlendFunc(GL_ONE, GL_ONE);
    if( !ShaderManager::useShader(shader)){
        ShaderManager::useShader(shader);
        shader->use();
        shader->setVec3("cameraPos", Runtime::getCamera()->getGameObject()->getWorldPosition());
        shader->setMat4("projection", Runtime::getCamera()->getProjectionMatrix());
        shader->setMat4("view", Runtime::getCamera()->getViewMatrix());
        shader->setMat4("ortho", ortho);
    }
    shader->setVec3("anchor", anchor->getWorldPosition() + offset);
    shader->setFloat("size", scale);
    for (auto it = bundles.begin();it != bundles.end();) {

        it->draw( shader );
        if (it->end()) it = bundles.erase(it);
        if (it == bundles.end()) break;
        it++;
    }


    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glDepthMask(GL_TRUE);
}

void ParticleFactory::start() {
    ShaderManager::loadShader("pf", "particle/pf", "particle/pf", "particle/pf");
    shader = ShaderManager::getShader("pf");
    ortho = glm::ortho(0.0f, (float)Utility::SCREEN_WIDTH, (float)0, (float)Utility::SCREEN_HEIGHT);
    spot =  TextureManager::loadTexture2D(
            Utility::RESOURCE_PREFIX + "Textures/particle/spot.png"
    );
    fog = TextureManager::loadTexture2D(
            Utility::RESOURCE_PREFIX + "Textures/particle/fog.jpg"
    );

}

ParticleFactory::ParticleFactory(GameObject *anchor, float scale, glm::vec3 offset) : anchor(anchor), scale(scale), offset(offset) {}

void ParticleFactory::addExplosion() {
    if (bundles.size() < 2) {
        bundles.push_back(ParticleBundle(1, false));
        auto& it = bundles.back();
        it.visible = false;
        it.texture = spot;
        bundles.push_back(ParticleBundle(1, false));
        auto& iit = bundles.back();
        iit.visible = false;
        iit.texture = fog;
    }
    bundles.push_back(ParticleBundle(200, false));
    auto& it = bundles.back();

    it.texture = spot;

    it.updateFunc = ParticleBundle::firePUpd;

    bundles.push_back(ParticleBundle(4, false));
    auto& iit = bundles.back();

    iit.texture = fog;

    iit.width = 2048;
    iit.height = 2048;
    iit.updateFunc = ParticleBundle::smogUpd;
    iit.generateFunc = ParticleBundle::smogGen;

}
