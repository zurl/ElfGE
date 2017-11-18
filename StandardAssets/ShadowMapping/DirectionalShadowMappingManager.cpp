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
    glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT, Utility::SCREEN_WIDTH, Utility::SCREEN_HEIGHT, 0, GL_DEPTH_COMPONENT, GL_UNSIGNED_BYTE, NULL);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    //glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, textureColorbuffer, 0);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, textureColorbuffer, 0);
    // create a renderbuffer object for depth and stencil attachment (we won't be sampling these)

    //glGenRenderbuffers(1, &rbo);
    //glBindRenderbuffer(GL_RENDERBUFFER, rbo);
    //glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, Utility::SCREEN_WIDTH, Utility::SCREEN_HEIGHT); // use a single renderbuffer object for both a depth AND stencil buffer.
    //glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, rbo); // now actually attach it
    // now that we actually created the framebuffer and added all attachments we want to check if it is actually complete now
    if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
        std::cout << "ERROR::FRAMEBUFFER:: Framebuffer is not complete!" << std::endl;
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
    shader = ShaderManager::getShader("directional_shadow");
}

void DirectionalShadowMappingManager::computeMapping() {
    glBindFramebuffer(GL_FRAMEBUFFER, framebuffer);
    glEnable(GL_DEPTH_TEST); // enable depth testing (is disabled for rendering screen-space quad)

    // make sure we clear the framebuffer's content
    glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    shader->use();

    float near_plane = 1.0f, far_plane = 7.5f;
    projection = glm::ortho(-10.0f, 10.0f, -10.0f, 10.0f, near_plane, far_plane);
    shader->setMat4("projection", projection);
    view = glm::lookAt(getPosition(),
                getPosition() + glm::rotate(glm::quat(glm::vec3(0, 0, -0.5)), Transform::forward),
                Transform::up);
    shader->setMat4("view", view);
}

void DirectionalShadowMappingManager::applyMapping(Shader * shader) {
    glActiveTexture(GL_TEXTURE8);
    glBindTexture(GL_TEXTURE_2D, textureColorbuffer);
    shader->setVec3("shadowLightPos", getPosition());
    shader->setInt("shadowMap", 8);
    shader->setMat4("lightSpaceMatrix",
                    projection * view);
}

const glm::vec3 &DirectionalShadowMappingManager::getPosition() const {
    return position;
}

void DirectionalShadowMappingManager::setPosition(const glm::vec3 &position) {
    DirectionalShadowMappingManager::position = position;
}

DirectionalShadowMappingManager::DirectionalShadowMappingManager(const glm::vec3 &position, int resolution)
        : resolution(resolution), position(position) {}

DirectionalShadowMappingManager::~DirectionalShadowMappingManager() {

}
