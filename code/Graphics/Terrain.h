//
// Created by Xarvie on 12/5/2019.
//

#ifndef INC_3D_TERRAIN_H
#define INC_3D_TERRAIN_H

#include "Shader.h"
#include <cmath>
#include <iostream>

#define STB_IMAGE_IMPLEMENTATION1
#include "stb_image.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Camera.h"
#include <map>
#include <unordered_map>
#include <tuple>
//#include "BlockQueue.h"
#include "noise.h"


#define T_1

#if defined(T_1)


#define XYZ(x, y, z) ((x) * BLOCK_SIZE2 * BLOCK_SIZE2 + (y) * BLOCK_SIZE2 + (z))
#define XYZW(x, y, z) (((char)x << 8 << 8 << 8) | ((char)y << 8 << 8)  | ((char)z << 8) | (0xff))
typedef int PosT;
#define Pos(x,y,z) (XYZ(x,y,z))

#else
typedef std::tuple<short, short, short> PosT;
#define Pos(x,y,z) (PosT(x,y,z))
#endif

#define GLARR 10

enum Terrain{
    VISIABLE_SIZE = 16,
    BLOCK_SIZE = 16,
    BLOCK_SIZE2 = BLOCK_SIZE+2,
};

class Cube{
public:
    glm::vec3 xyz;
    char t;
};
class Block;
//typedef moodycamel::BlockingConcurrentQueue<Block*> WorkQueue;
//typedef moodycamel::ConcurrentQueue<Block*> ResultQueue;
typedef void (*world_func)(int, int, int, int, void *);

class Block{
public:
#if defined(T_1)
    std::vector<Cube> cubes;
#else
    std::map<PosT, Cube> cubes;
#endif
    std::vector<GLfloat> vertices;
    int faceNum;
    int cubeNum;
    glm::vec3 xyz;
    GLuint VBO;
    GLuint VAO;
    GLuint VAO2;

    int init(int bx, int by, int bz);
    int buildBlockVertices();
    //int BuildBlockVerticesTask(WorkQueue& inputQueue);
    int delBuffer();
    int BindBuffer();

    int makeTerrain();

};

class World{
public:

    std::map<std::tuple<int, int, int>, Block>blockMap;
    class RenderTask{
    public:
        std::vector<Block>blocks;

    };
public:
    int drawModels(int depth);
    int renderInit();
    Block* findBlock(int bx, int by, int bz);
    Block* addBlock(int bx, int by, int bz);
    int delBlock(Block* bl);
    int addCube(float gx, float gy, float gz, char t);
    int delCube(float gx, float gy, float gz);
    int refreshAroundBlockPos(float bx, float by, float bz);
    int refreshAroundBlockBegin(float cx, float cy, float cz, char t);
    int refreshAroundBlockEnd();
    Block* makeTerrainByBXYZ(float gx, float gy, float gz);
    Block * makeTerrain(float gx, float gy, float gz);
    Block * makePlane(float gx, float gy, float gz);
    Block * makeFixedPlane(float gx, float gy, float gz, int mx, int my, int mz);
    Block * findBlockByPos(float gx, float gy, float gz);
    static std::tuple<int, int, int>gPosTobPos(float gx, float gy, float gz);
    int getAroundBlockInfo(Block* centerBlock);
    //int initWorld();

    Shader * shaderDrawSceneT = nullptr;
    Shader * shaderDrawSceneDepth = nullptr;
    unsigned int texture_a = 0, texture_d = 0, texture_t = 0;


};
static void allocWorld(){
    std::cout << ((0x7f << 8 << 8 << 8) | (0xff << 8 << 8)  | (0xff << 8) | (0xff)) << std::endl;

}


static std::pair<int, int> gen_buffer(GLsizei size, GLfloat *data) {


    return std::pair<int, int>(0, 0);
}
#endif //INC_3D_TERRAIN_H
