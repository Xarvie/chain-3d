//
// Created by caspasex on 2020/7/1.
//

#ifndef INC_3D_PARTICLE_H
#define INC_3D_PARTICLE_H

#include "Config.h"
#include "OpenglHeader.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
using namespace glm;

class Particle{
public:
    struct ParticleElement{
        glm::vec3 pos, speed;
        unsigned char r,g,b,a;
        float size, angle, weight;
        float life;
        float cameraDistance;

        bool operator<(const ParticleElement& that) const {
            return this->cameraDistance > that.cameraDistance;
        }
    };

public:
    int init();
    int draw();

public:
    GLuint particlesPositionBuffer = 0;
    GLuint particlesColorBuffer = 0;
    glm::mat4 viewProjectionMatrix{};
    GLuint billboardVertexBuffer = 0;
    GLuint vertexArrayID = 0;
};

#endif //INC_3D_PARTICLE_H
