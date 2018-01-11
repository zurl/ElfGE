//
// Created by sky on 2017/12/21.
//

#ifndef ELFGE_GRASSRENDERER_H
#define ELFGE_GRASSRENDERER_H

#include <GameEngine.h>
#include <Meshs/PlaneMesh.h>
#include <random>

class GrassRenderer : public Component {
    const int BLADE_SEGS = 4;// # of blade segments
    const unsigned int BLADE_VERTS = (BLADE_SEGS + 1) * 2;// # of vertices per blade (1 side)
    const int BLADE_INDICES = BLADE_SEGS * 12;
    const float BLADE_WIDTH = 0.15;
    const float BLADE_HEIGHT_MIN = 1.25;
    const float BLADE_HEIGHT_MAX = 2.0;

    int numBlades = 5000;
    float radius = 10; // half the width of the square
    glm::vec3 fogColor = glm::vec3(0.74f, 0.77f, 0.91f);
    glm::vec3 grassColor = glm::vec3(0.45f, 0.46f, 0.19f);

    float fogFar = radius * 20, grassFogFar =
            radius * 2, transitionLow = 0.31, transitionHigh = 0.36, windIntensity = 1.5;
    glm::vec3 heightMapScale = glm::vec3(1 / 3072.0f, 1 / 3072.0f, 180.0f);

    GLuint texture, heightMap;
    Shader *shader;
    std::vector<float> vindex, shape, offset;
    std::vector<GLuint> index;

    GLuint VAO, vindexVBO, shapeVBO, offsetVBO, EBO;


public:
    GrassRenderer(const std::string &UV, const std::string &height);

    void initBladeIndices();

    void initBladeShapeVerts();

    void initBladeOffsetVerts();

    void initBladeIndexVerts();

    float randomGen();

    void prepare();

    void bindVertice();

    void updateGraphics(RenderLayer renderLayer);
};


#endif //ELFGE_GRASSRENDERER_H
