//
// Created by 张程易 on 30/12/2017.
//

#ifndef ELFGE_PARTICLEBUNDLE_H
#define ELFGE_PARTICLEBUNDLE_H

#include "GameEngine.h"

class ParticleBundle {
public:
    struct Particle {
        glm::vec3 position;
        glm::vec3 velocity;
        glm::vec4 tone;
        GLfloat zoom;
        GLuint lifespan;
    };

    typedef std::function<bool(Particle&)> ParticleUpdate; // if Particle is still alive return 1


    static bool defaultUpdate(Particle& p) {
        if (p.lifespan-- <= 0) { // if a kid never dies out ,lifespan shall not change.
            return false;
        }
        p.position += p.velocity;
        p.velocity.y -= 0.0003f;

        return true;
    }
    static bool defaultGenerate(Particle& p) {
        p.lifespan = 80;
        p.position = { 0 , 0 , 0 };
        p.tone = { 1.8,1.05,0.25,1.0 };
        p.zoom = 1.0;
        p.velocity = { (rand() % 40 / 200.0) - 0.1 , (rand() % 20 / 200.0)-0.01,(rand() % 40 / 200.0) - 0.1 };
        return true;
    }
    static bool smogGen(Particle& p) {
        p.lifespan = 80;
        p.position = { rand() % 100 / 100.0 - 0.5f,rand() % 10 / 100.0 + 0.5f,rand() % 100 / 100.0 - 0.5f };
        p.velocity = { rand() % 100 / 100.0, rand() % 100 / 100.0, rand() % 100 / 100.0 };
        p.tone = { 1.0f,0.1f,0.0f,0.0f };
        p.zoom = 0.5;
        return true;
    }
    static bool smogUpd(Particle& p) {
        if (p.lifespan-- <= 0) { // if a kid never dies out ,lifespan shall not change.
            p.lifespan = 0;
            return false;
        }
        if (p.lifespan >= 60 && p.lifespan <= 80) {
            p.tone.a -= (p.tone.a - 1.0) / 10.0;
        }
        else {
            p.tone.a = p.lifespan / 40.0;
            if (p.tone.a > 1) p.tone.a = 1.0;
        }
        p.zoom += rand() % 10 / 100.0;
        return true;
    }

    static bool firePUpd(Particle& p) {

        if (p.lifespan-- <= 0) { // if a kid never dies out ,lifespan shall not change.
            p.lifespan = 0;
            return false;

        }
        p.position += p.velocity;
        //glm::vec3 anchor = ParticleFactory::Instance().bundles.begin()->anchor;

        /*if (terrain.getHeight(anchor.x + p.position.x, anchor.z + p.position.z) >= p.position.y + anchor.y)
        {
        p.velocity.y = -p.velocity.y;
        }*/

        p.velocity.x -= (p.velocity.x - 0) / 60.0;
        p.velocity.z -= (p.velocity.z - 0) / 60.0;
        p.velocity.y -= (p.velocity.y + 0.1) / 300.0;
        p.tone.a = p.lifespan / 40.0;

        return true;

    };
    ParticleUpdate updateFunc;
    ParticleUpdate generateFunc;
    unsigned int texture;
    int width, height;
    bool loop;
    int size;
    int lifespan;
    int count;
    bool visible;
    std::vector<Particle> kids;
    ParticleBundle(int num=32,bool _loop=false,ParticleUpdate _u = ParticleBundle::defaultUpdate,
                   ParticleUpdate _g = ParticleBundle::defaultGenerate);

    void refresh();

    void update();

    void draw(Shader * shader);

    const bool end() const {
        return count <= 0 && !loop;
    }
private:
    GLuint VAO, VBO;
};


#endif //ELFGE_PARTICLEBUNDLE_H
