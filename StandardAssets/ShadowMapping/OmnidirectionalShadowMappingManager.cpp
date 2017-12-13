//
// Created by 张程易 on 18/11/2017.
//

#include "OmnidirectionalShadowMappingManager.h"

void OmnidirectionalShadowMappingManager::initialize() {
    glGenFramebuffers(1, &depthMapFBO);
    glGenTextures(1, &depthCubemap);
    glBindTexture(GL_TEXTURE_CUBE_MAP, depthCubemap);
    for (GLuint i = 0; i < 6; ++i)
        glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_DEPTH_COMPONENT,
                     resolution, resolution, 0, GL_DEPTH_COMPONENT, GL_FLOAT, NULL);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
    glBindFramebuffer(GL_FRAMEBUFFER, depthMapFBO);
    glFramebufferTexture(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, depthCubemap, 0);
    if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
        std::cout << "ERROR::FRAMEBUFFER:: Framebuffer is not complete!" << std::endl;
    glDrawBuffer(GL_NONE);
    glReadBuffer(GL_NONE);
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
    ShaderManager::loadShader("omnidirectional_shadow", "omnidirectional_shadow", "omnidirectional_shadow",
                              "omnidirectional_shadow");
    shader = ShaderManager::getShader("omnidirectional_shadow");
}

void OmnidirectionalShadowMappingManager::computeMapping() {
    glBindFramebuffer(GL_FRAMEBUFFER, depthMapFBO);
    glEnable(GL_DEPTH_TEST);
    glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    shader->use();

    GLfloat aspect = 1.0f;
    GLfloat near = 1.0f;
    GLfloat far = 25.0f;
    glm::mat4 shadowProj = glm::perspective(glm::radians(90.0f), aspect, near, far);
    std::vector<glm::mat4> shadowViews;
    glm::vec3 lightPos = pointLighting->getGameObject()->transform.getPosition();
    shadowViews.push_back(glm::lookAt(lightPos, lightPos + glm::vec3(1.0, 0.0, 0.0), glm::vec3(0.0, -1.0, 0.0)));
    shadowViews.push_back(glm::lookAt(lightPos, lightPos + glm::vec3(-1.0, 0.0, 0.0), glm::vec3(0.0, -1.0, 0.0)));
    shadowViews.push_back(glm::lookAt(lightPos, lightPos + glm::vec3(0.0, 1.0, 0.0), glm::vec3(0.0, 0.0, 1.0)));
    shadowViews.push_back(glm::lookAt(lightPos, lightPos + glm::vec3(0.0, -1.0, 0.0), glm::vec3(0.0, 0.0, -1.0)));
    shadowViews.push_back(glm::lookAt(lightPos, lightPos + glm::vec3(0.0, 0.0, 1.0), glm::vec3(0.0, -1.0, 0.0)));
    shadowViews.push_back(glm::lookAt(lightPos, lightPos + glm::vec3(0.0, 0.0, -1.0), glm::vec3(0.0, -1.0, 0.0)));
    shader->setMat4("projection", shadowProj);
    for (GLuint i = 0; i < 6; ++i) {
        shader->setMat4("views[" + std::to_string(i) + "]", shadowViews[i]);
    }
    glViewport(0, 0, resolution, resolution);
    shader->setVec3("shadowLightPos", pointLighting->getGameObject()->transform.getPosition());
    shader->setFloat("far_plane", 25.0f);
    shader->setInt("enableBones", 0);
}

void OmnidirectionalShadowMappingManager::applyMapping(Shader *shader) {
    glActiveTexture(GL_TEXTURE8);
    glBindTexture(GL_TEXTURE_CUBE_MAP, depthCubemap);
    shader->setInt("shadowMap", 8);
    shader->setVec3("shadowLightPos", pointLighting->getGameObject()->transform.getPosition());
    shader->setFloat("far_plane", 25.0f);
}

OmnidirectionalShadowMappingManager::OmnidirectionalShadowMappingManager(PointLighting *pointLighting, int resolution)
        : pointLighting(pointLighting), resolution(resolution) {}

Shader *OmnidirectionalShadowMappingManager::getShader() {
    return shader;
}
