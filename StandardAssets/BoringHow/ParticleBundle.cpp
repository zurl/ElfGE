//
// Created by 张程易 on 30/12/2017.
//

#include "ParticleBundle.h"

ParticleBundle::ParticleBundle(int num, bool _loop, ParticleUpdate _u, ParticleUpdate _g) :
        size(num),
        loop(_loop),
        updateFunc(_u),
        generateFunc(_g),
        lifespan(0),
        width(64),
        height(128),
        texture(0),
        visible(true)
{
    refresh();
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    //printf((const char*)glewGetErrorString(glGetError()));
    glBufferData(GL_ARRAY_BUFFER, sizeof(Particle) * size, NULL, GL_STATIC_DRAW);
    //printf((const char*)glewGetErrorString(glGetError()));
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Particle), (GLvoid*)offsetof(Particle,position));
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(Particle), (GLvoid*)offsetof(Particle, tone));
    glEnableVertexAttribArray(2);
    glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(Particle), (GLvoid*)offsetof(Particle, velocity));
    glEnableVertexAttribArray(3);
    glVertexAttribIPointer(3, 1, GL_INT, sizeof(Particle), (GLvoid*)offsetof(Particle, lifespan));
    glEnableVertexAttribArray(4);
    glVertexAttribPointer(4, 1, GL_FLOAT, GL_FALSE, sizeof(Particle), (GLvoid*)offsetof(Particle, zoom));

    //printf((const char*)glewGetErrorString(glGetError()));
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    //printf((const char*)glewGetErrorString(glGetError()));
    glBindVertexArray(0);
}

void ParticleBundle::refresh() {
    count = size;
    kids.resize(size);
    for (int i = 0;i < size;i++)
    {
        generateFunc(kids[i]);
    }
}

void ParticleBundle::update() {

    for (std::vector<Particle>::iterator i = kids.begin();i != kids.end();)
    {
        //if (!updateFunc(*i))	i = kids.erase(i);
        if(!updateFunc(*i)) count--;
        i++;
    }
    if (count <= 0)
        if (loop) refresh();
}
/*
 *
uniform vec3 cameraPos;
uniform mat4 ortho;
uniform int width;
uniform int height;
uniform mat4 view;
uniform vec3 anchor;
uniform mat4 projection;


 */
void ParticleBundle::draw(Shader * shader){
    if (!visible) return;
    update();
    if (end()) return;

    shader->setInt("width", width);
    shader->setInt("height", height);
    shader->setInt("tex", 1);
    glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_2D, this->texture);



    glActiveTexture(GL_TEXTURE0);
    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(Particle)*kids.size(), &kids[0], GL_STATIC_DRAW);
    glDrawArrays(GL_POINTS, 0, kids.size());
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    glBindVertexArray(0);
}

