//
// Created by caspase on 8/20/2020.
//

#ifndef INC_3D_STANDARDPROGRAM_H
#define INC_3D_STANDARDPROGRAM_H

#include "Config.h"

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <vector>
#include "Program.h"

#define struct_offset(s, m) (&(((s*)0)->m))

namespace Simple2D {



    enum StandardProgramType {
        SPT_Color,
        SPT_Sprite,
        SPT_Particle,
        SPT_Count
    };

    struct SpriteVertexFormat {
        glm::vec3 position;
        glm::vec2 texcoord;
        Color color;
        float texindex;
    };

    struct ColorVertexFormat {
        glm::vec3 position;
        Color color;
    };

    class StandardProgram {
    public:
        StandardProgram();

        ~StandardProgram();

        Program *GetProgram(StandardProgramType type);

    private:
        Program *vStandardPrograms[StandardProgramType::SPT_Count];
    };
}

#endif //INC_3D_STANDARDPROGRAM_H
