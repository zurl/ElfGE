//
// Created by 张程易 on 17/11/2017.
//

#include "DirectionalShadowMappingManager.h"

void DirectionalShadowMappingManager::initialize() {
    glGenFramebuffers(1, &framebuffer);
    glBindFramebuffer(GL_FRAMEBUFFER, framebuffer);
    // create a color attachment texture

    glGenTextures(1, &textureColorbuffer);
    glBindTexture(GL_TEXTURE_2D, textureColorbuffer);
    //glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, Utility::SCREEN_WIDTH, Utility::SCREEN_HEIGHT, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT, resolution, resolution, 0, GL_DEPTH_COMPONENT, GL_UNSIGNED_BYTE,
                 NULL);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);
    GLfloat borderColor[] = {1.0, 1.0, 1.0, 1.0};
    glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, borderColor);
    //glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, textureColorbuffer, 0);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, textureColorbuffer, 0);
    if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
        std::cout << "ERROR::FRAMEBUFFER:: Framebuffer is not complete!" << std::endl;
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
    shader = ShaderManager::getShader("directional_shadow");
}

void DirectionalShadowMappingManager::computeMapping() {
    glBindFramebuffer(GL_FRAMEBUFFER, framebuffer);
    glEnable(GL_DEPTH_TEST);
    glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    shader->use();
    glViewport(0, 0, resolution, resolution);
    float near_plane = 1.0f, far_plane = 20.5f;
    projection = glm::ortho(-10.0f, 10.0f, -10.0f, 10.0f, near_plane, far_plane);
    shader->setMat4("projection", projection);
    view = glm::lookAt(directLighting->getGameObject()->transform.getPosition(),
                       directLighting->getGameObject()->transform.getPosition()
                       + glm::rotate(directLighting->getGameObject()->transform.getQuaternion(), Transform::forward),
                       Transform::up);
    shader->setMat4("view", view);
    shader->setInt("enableBones", 1);
}

void DirectionalShadowMappingManager::applyMapping(Shader *shader) {
    glActiveTexture(GL_TEXTURE8);
    glBindTexture(GL_TEXTURE_2D, textureColorbuffer);
    shader->setVec3("shadowLightPos", directLighting->getGameObject()->transform.getPosition());
    shader->setInt("shadowMap", 8);
    shader->setMat4("lightSpaceMatrix", projection * view);
}

DirectionalShadowMappingManager::DirectionalShadowMappingManager(DirectLighting *directLighting, int resolution)
        : resolution(resolution), directLighting(directLighting) {}

DirectionalShadowMappingManager::~DirectionalShadowMappingManager() {

}

Shader *DirectionalShadowMappingManager::getShader() {
    return shader;
}
