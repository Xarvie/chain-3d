//
// Created by Xarvie on 12/5/2019.
//

#include "Terrain.h"
#include "Data.h"
#include "map.h"
#include "Render.h"
#include "ResourceMgr.h"

int World::drawModels(int depth){
    if(depth == 0)
    {
        shaderDrawSceneT->use();
        glm::mat4 model(1.0f);
        model = translate(model, glm::vec3(-0.5, 0.0f, -0.5));
        glm::mat4 view = worldData->camera.getViewMatrix();
        glUniformMatrix4fv(glGetUniformLocation(shaderDrawSceneT->ID, "projection"), 1, GL_FALSE, glm::value_ptr(worldData->proj));
        glUniformMatrix4fv(glGetUniformLocation(shaderDrawSceneT->ID, "view"), 1, GL_FALSE, glm::value_ptr(view));
        glUniformMatrix4fv(glGetUniformLocation(shaderDrawSceneT->ID, "M"), 1, GL_FALSE, glm::value_ptr(model));

        glUniform1i(glGetUniformLocation(shaderDrawSceneT->ID, "shadowMap"), 0);

        glUniform1i(glGetUniformLocation(shaderDrawSceneT->ID, "diffuseTexture_a"), 1);
        glUniform1i(glGetUniformLocation(shaderDrawSceneT->ID, "diffuseTexture_t"), 2);
        glUniform1i(glGetUniformLocation(shaderDrawSceneT->ID, "diffuseTexture_d"), 3);

        {
            shaderDrawSceneT->setMat4("lightSpaceMatrix", worldData->lightSpaceMatrix);
            shaderDrawSceneT->setVec3("lightPos", worldData->light2Pos);
            shaderDrawSceneT->setInt("shadowMap", 0);
            if (worldData->shadowOn)
                shaderDrawSceneT->setInt("shadowOn", 1);
            else
                shaderDrawSceneT->setInt("shadowOn", 0);

            shaderDrawSceneT->setVec3("light.direction", worldData->light1Pos.x,  worldData->light1Pos.y,  worldData->light1Pos.z);
        }

        if(worldData->shadowOn == 1)
        {
            glActiveTexture(GL_TEXTURE0);
            glBindTexture(GL_TEXTURE_2D, Render::depthMap);
            glActiveTexture(GL_TEXTURE0+1);
            glBindTexture(GL_TEXTURE_2D, texture_a);
            glActiveTexture(GL_TEXTURE1+1);
            glBindTexture(GL_TEXTURE_2D, texture_t);
            glActiveTexture(GL_TEXTURE2+1);
            glBindTexture(GL_TEXTURE_2D, texture_d);
        } else{
            glActiveTexture(GL_TEXTURE0);
            glBindTexture(GL_TEXTURE_2D, texture_a);
            glActiveTexture(GL_TEXTURE1);
            glBindTexture(GL_TEXTURE_2D, texture_t);
            glActiveTexture(GL_TEXTURE2);
            glBindTexture(GL_TEXTURE_2D, texture_d);
        }


        {
            for (auto &E : this->blockMap) {
                auto &b = E.second;
                auto &VAO = b.VAO2;

                glBindVertexArray(VAO);

                glDrawArrays(GL_TRIANGLES, 0, b.faceNum * 6);

                glBindVertexArray(0);
            }
        }
    } else{
        shaderDrawSceneDepth->use();
        glm::mat4 model(1.0f);
        model = translate(model, glm::vec3(-0.5, 0.0f, -0.5));
        glm::mat4 view = worldData->camera.getViewMatrix();


        {
            shaderDrawSceneDepth->setMat4("M", model);
            shaderDrawSceneDepth->setMat4("lightSpaceMatrix", worldData->lightSpaceMatrix);
        }


        {
            for (auto &E : this->blockMap) {
                auto &b = E.second;
                auto &VAO = b.VAO2;

                glBindVertexArray(VAO);

                glDrawArrays(GL_TRIANGLES, 0, b.faceNum * 6);

                glBindVertexArray(0);
            }
        }
    }
    return 0;
}


int World::renderInit()
{

    // texture 1
    // ---------
    {
        glGenTextures(1, &texture_a);
        glBindTexture(GL_TEXTURE_2D, texture_a);
        // set the texture wrapping parameters
        //glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        //glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        // set texture filtering parameters
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
        // load image, create texture and generate mipmaps
        int width, height, nrChannels;
        stbi_set_flip_vertically_on_load(true); // tell stb_image.h to flip loaded texture's on the y-axis.
        auto resData = res.Res("texture_t1.png");
        unsigned char *data = stbi_load_from_memory((stbi_uc*)resData.data(), resData.size(), &width, &height, &nrChannels, 0);
        if (data) {
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
            //glGenerateMipmap(GL_TEXTURE_2D);
        } else {
            std::cout << "Failed to load texture" << std::endl;
        }
        stbi_image_free(data);
    }
    {
        glGenTextures(1, &texture_t);
        glBindTexture(GL_TEXTURE_2D, texture_t);
        // set the texture wrapping parameters
        //glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        //glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        // set texture filtering parameters
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
        // load image, create texture and generate mipmaps
        int width, height, nrChannels;
        stbi_set_flip_vertically_on_load(true); // tell stb_image.h to flip loaded texture's on the y-axis.
        auto resData = res.Res("texture_t1.png");
        unsigned char *data = stbi_load_from_memory((stbi_uc*)resData.data(), resData.size(), &width, &height, &nrChannels, 0);
        if (data) {
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
            //glGenerateMipmap(GL_TEXTURE_2D);
        } else {
            std::cout << "Failed to load texture" << std::endl;
        }
        stbi_image_free(data);
    }
    stbi_set_flip_vertically_on_load(false);



    {
        glGenTextures(1, &texture_d);
        glBindTexture(GL_TEXTURE_2D, texture_d);
        // set the texture wrapping parameters
        //glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        //glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        // set texture filtering parameters
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
        // load image, create texture and generate mipmaps
        int width, height, nrChannels;
        stbi_set_flip_vertically_on_load(true); // tell stb_image.h to flip loaded texture's on the y-axis.
        auto resData = res.Res("texture_t1.png");
        unsigned char *data = stbi_load_from_memory((stbi_uc*)resData.data(), resData.size(), &width, &height, &nrChannels, 0);
        if (data) {
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
            //glGenerateMipmap(GL_TEXTURE_2D);
        } else {
            std::cout << "Failed to load texture" << std::endl;
        }
        stbi_image_free(data);
    }



    glBindTexture(GL_TEXTURE_2D, 0);
//    {
//        int halfLen = 1;
//        for (int ix = -halfLen; ix <= halfLen; ix++) {
//            for (int iy = 0; iy <= 1; iy++) {
//                for (int iz = -halfLen; iz <= halfLen; iz++) {
//                    this->makeTerrain(ix * BLOCK_SIZE, iy * BLOCK_SIZE, iz * BLOCK_SIZE);
//                }
//            }
//        }
//    }

//    {
//        int halfLen = 1;
//        for (int ix = -halfLen; ix <= halfLen; ix++) {
//            for (int iy = 0; iy < 1; iy++) {
//                for (int iz = -halfLen; iz <= halfLen; iz++) {
//                    this->makePlane(ix * BLOCK_SIZE, iy * BLOCK_SIZE, iz * BLOCK_SIZE);
//                }
//            }
//        }
//    }

    this->makeFixedPlane(0, 0, 0, 15, 15, 15);

    {
        std::vector<Block *> tmpBlockVec;
        for (auto &E : this->blockMap) {
            auto &b = E.second;

            tmpBlockVec.push_back(&b);

        }
        for (auto &E : tmpBlockVec) {
            Block *bl = E;
            this->getAroundBlockInfo(bl);
        }
    }
    for (auto &E : this->blockMap) {
        auto &b = E.second;
        b.delBuffer();
        b.buildBlockVertices();
        b.BindBuffer();

        auto &VAO = b.VAO2;
        auto &VBO = b.VBO;

        glBindVertexArray(VAO);
        glBindBuffer(GL_ARRAY_BUFFER, VBO);

        glEnableVertexAttribArray(0);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, GLARR * sizeof(float), (void *) 0);

        glEnableVertexAttribArray(1);
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, GLARR * sizeof(float), (void *) (3 * sizeof(float)));

        glEnableVertexAttribArray(2);
        glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, GLARR * sizeof(float), (void *) (6 * sizeof(float)));

        glEnableVertexAttribArray(3);
        glVertexAttribPointer(3, 1, GL_FLOAT, GL_FALSE, GLARR * sizeof(float), (void *) (8 * sizeof(float)));

        glEnableVertexAttribArray(4);
        glVertexAttribPointer(4, 1, GL_FLOAT, GL_FALSE, GLARR * sizeof(float), (void *) (9 * sizeof(float)));

        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glBindVertexArray(0);
    }
    std::vector<char>TerrainVoxelVert;
    std::vector<char>TerrainVoxelFrag;
    TerrainVoxelVert.insert(TerrainVoxelVert.end(), TerrainVoxel_vert_glsl, TerrainVoxel_vert_glsl + strlen(TerrainVoxel_vert_glsl));
    TerrainVoxelFrag.insert(TerrainVoxelFrag.end(), TerrainVoxel_frag_glsl, TerrainVoxel_frag_glsl + strlen(TerrainVoxel_frag_glsl));

//    auto && TerrainVoxelVert = res.Res("Shader/TerrainVoxel.vert.glsl");
//    auto && TerrainVoxelFrag = res.Res("Shader/TerrainVoxel.frag.glsl");

    shaderDrawSceneT = new Shader(TerrainVoxelVert, TerrainVoxelFrag);

    std::vector<char>ShadowMappingDepthStaticVert;
    std::vector<char>ShadowMappingDepthStaticFrag;
    ShadowMappingDepthStaticVert.insert(ShadowMappingDepthStaticVert.end(), ShadowMappingDepthStatic_vert_glsl, ShadowMappingDepthStatic_vert_glsl + strlen(ShadowMappingDepthStatic_vert_glsl));
    ShadowMappingDepthStaticFrag.insert(ShadowMappingDepthStaticFrag.end(), ShadowMappingDepthStatic_frag_glsl, ShadowMappingDepthStatic_frag_glsl + strlen(ShadowMappingDepthStatic_frag_glsl));
//
//    auto && ShadowMappingDepthStaticVert = res.Res("Shader/ShadowMappingDepthStatic.vert.glsl");
//    auto && ShadowMappingDepthStaticFrag = res.Res("Shader/ShadowMappingDepthStatic.frag.glsl");
    shaderDrawSceneDepth = new Shader(ShadowMappingDepthStaticVert, ShadowMappingDepthStaticFrag);

    return 0;
}
Block *World::findBlock(int x, int y, int z) {
    auto it = this->blockMap.find(std::tuple<int, int, int>(x, y, z));
    if (it == this->blockMap.end())
        return nullptr;
    return &it->second;
}

int World::getAroundBlockInfo(Block *centerBlock) {
    {
        int _dir = 1;
        Block tmpBl;
        tmpBl.init(0, 0, 0);
        std::vector<Block *> blVec(3 * 3 * 3, &tmpBl);
        for (int x = -_dir; x <= _dir; x++) {
            for (int y = -_dir; y <= _dir; y++) {
                for (int z = -_dir; z <= _dir; z++) {
                    Block *bl = this->findBlock(centerBlock->xyz.x + x, centerBlock->xyz.y + y,
                                                centerBlock->xyz.z + z);
                    if (bl == NULL) {
                        bl = &tmpBl;
                    }
                    blVec[(x + 1) * 3 * 3 + (y + 1) * 3 + (z + 1)] = bl;
                }
            }
        }


        for (int x = BLOCK_SIZE - 1, centX = 0; centX < BLOCK_SIZE + 2; x++, centX++) {
            for (int y = BLOCK_SIZE - 1, centY = 0; centY < BLOCK_SIZE + 2; y++, centY++) {
                for (int z = BLOCK_SIZE - 1, centZ = 0; centZ < BLOCK_SIZE + 2; z++, centZ++) {
                    Block *bxv = blVec[((int) (x / BLOCK_SIZE)) * 3 * 3 +
                                       ((int) (y / BLOCK_SIZE)) * 3 +
                                       ((int) (z / BLOCK_SIZE))];
                    auto xbb = bxv->cubes[Pos(
                            (x % BLOCK_SIZE) + 1, (y % BLOCK_SIZE) + 1, (z % BLOCK_SIZE) + 1)];

                    centerBlock->cubes[Pos(centX, centY, centZ)].t = xbb.t;
                }
            }
        }
    }
    return 0;
}

Block *World::addBlock(int bx, int by, int bz) {
    Block &bl = blockMap[std::tuple<int, int, int>(bx, by, bz)];
    bl.init(bx, by, bz);
    return &bl;
}

int World::delBlock(Block *bl) {
    blockMap.erase(std::tuple<int, int, int>(bl->xyz.x, bl->xyz.y, bl->xyz.z));

    glDeleteVertexArrays(1, &bl->VAO);
    glDeleteVertexArrays(1, &bl->VAO2);
    glDeleteBuffers(1, &bl->VBO);
    return 0;
}

std::tuple<int, int, int> World::gPosTobPos(float gx, float gy, float gz){
    int bx = gx / BLOCK_SIZE;
    int by = gy / BLOCK_SIZE;
    int bz = gz / BLOCK_SIZE;
    int ox = 0;
    int oy = 0;
    int oz = 0;
    if (gx < 0) {
        ox = gx - bx * BLOCK_SIZE;
        if (ox != 0) {
            ox += BLOCK_SIZE;
            bx -= 1;
        }
    }
    if (gy < 0) {
        oy = gy - by * BLOCK_SIZE;
        if (oy != 0) {
            oy += BLOCK_SIZE;
            by -= 1;
        }
    }
    if (gz < 0) {
        oz = gz - bz * BLOCK_SIZE;
        if (oz != 0) {
            oz += BLOCK_SIZE;
            bz -= 1;
        }
    }

    return std::tuple<int, int, int>(bx, by, bz);
}

Block *World::findBlockByPos(float gx, float gy, float gz) {
    int bx = gx / BLOCK_SIZE;
    int by = gy / BLOCK_SIZE;
    int bz = gz / BLOCK_SIZE;
    int ox = 0;
    int oy = 0;
    int oz = 0;
    if (gx < 0) {
        ox = gx - bx * BLOCK_SIZE;
        if (ox != 0) {
            ox += BLOCK_SIZE;
            bx -= 1;
        }
    }
    if (gy < 0) {
        oy = gy - by * BLOCK_SIZE;
        if (oy != 0) {
            oy += BLOCK_SIZE;
            by -= 1;
        }
    }
    if (gz < 0) {
        oz = gz - bz * BLOCK_SIZE;
        if (oz != 0) {
            oz += BLOCK_SIZE;
            bz -= 1;
        }
    }

    Block *bl = findBlock(bx, by, bz);
    return bl;
}


int World::addCube(float gx, float gy, float gz, char t) {
    int bx = gx / BLOCK_SIZE;
    int by = gy / BLOCK_SIZE;
    int bz = gz / BLOCK_SIZE;
    int ox = 0;
    int oy = 0;
    int oz = 0;
    if (gx < 0) {
        ox = gx - bx * BLOCK_SIZE;
        if (ox != 0) {
            ox += BLOCK_SIZE;
            bx -= 1;
        }
    }
    if (gy < 0) {
        oy = gy - by * BLOCK_SIZE;
        if (oy != 0) {
            oy += BLOCK_SIZE;
            by -= 1;
        }
    }
    if (gz < 0) {
        oz = gz - bz * BLOCK_SIZE;
        if (oz != 0) {
            oz += BLOCK_SIZE;
            bz -= 1;
        }
    }

    Block *bl = findBlock(bx, by, bz);
    if (!bl)
        bl = addBlock(bx, by, bz);

    int cx = ox;
    int cy = oy;
    int cz = oz;

    if (gx > 0) {
        cx = gx - bx * BLOCK_SIZE;
    }
    if (gy > 0) {
        cy = gy - by * BLOCK_SIZE;
    }
    if (gz > 0) {
        cz = gz - bz * BLOCK_SIZE;
    }


    Cube &cu = bl->cubes[Pos((1 + cx), (1 + cy), (1 + cz))];
    cu.xyz = glm::vec3(cx, cy, cz);
    cu.t = t;
    return 0;
}

std::vector<std::tuple<int, int, int, int>> _vec;

int blockx = 0;
int blocky = 0;
int blockz = 0;

int refreshAroundBlockPos(float bx, float by, float bz) {
    blockx = bx;
    blocky = by;
    blockz = bz;
    return 0;
}

int World::refreshAroundBlockBegin(float cx, float cy, float cz, char t) {

    _vec.push_back(std::tuple<int, int, int, int>(cx, cy, cz, t));

    if (cx == 0) {
        _vec.push_back(std::tuple<int, int, int, int>(cx, cy, cz, t));
        return 1;
    } else if (cx == BLOCK_SIZE - 1) {
        _vec.push_back(std::tuple<int, int, int, int>(cx, cy, cz, t));
        return 1;
    }

    if (cy == 0) {
        _vec.push_back(std::tuple<int, int, int, int>(cx, cy, cz, t));
        return 1;
    } else if (cy == BLOCK_SIZE - 1) {
        _vec.push_back(std::tuple<int, int, int, int>(cx, cy, cz, t));
        return 1;
    }
    if (cz == 0) {
        _vec.push_back(std::tuple<int, int, int, int>(cx, cy, cz, t));
        return 1;
    } else if (cz == BLOCK_SIZE - 1) {
        _vec.push_back(std::tuple<int, int, int, int>(cx, cy, cz, t));
        return 1;
    }
    return 0;
}

int World::refreshAroundBlockEnd() {
    if (_vec.size() == 0)
        return 0;


    std::map<std::tuple<int, int, int>, Block *> tmpBlockMap;

    Block *bl = findBlock(blockx, blocky, blockz);
    tmpBlockMap[std::tuple(blockx, blocky, blockz)] = bl;

    for (auto &E: _vec) {
        int cx = std::get<0>(E), cy = std::get<1>(E), cz = std::get<2>(E), t = std::get<3>(E);
        if (cx == 0) {

        } else if (cx == BLOCK_SIZE - 1) {
            return 1;
        }

        if (cy == 0) {
            return 1;
        } else if (cy == BLOCK_SIZE - 1) {
            return 1;
        }
        if (cz == 0) {
            return 1;
        } else if (cz == BLOCK_SIZE - 1) {
            return 1;
        }
    }

    return 0;
}

int World::delCube(float gx, float gy, float gz) {
    int bx = gx / BLOCK_SIZE;
    int by = gy / BLOCK_SIZE;
    int bz = gz / BLOCK_SIZE;
    int ox = 0;
    int oy = 0;
    int oz = 0;
    if (gx < 0) {
        ox = gx - bx * BLOCK_SIZE;
        if (ox != 0) {
            ox += BLOCK_SIZE;
            bx -= 1;
        }
    }
    if (gy < 0) {
        oy = gy - by * BLOCK_SIZE;
        if (oy != 0) {
            oy += BLOCK_SIZE;
            by -= 1;
        }
    }
    if (gz < 0) {
        oz = gz - bz * BLOCK_SIZE;
        if (oz != 0) {
            oz += BLOCK_SIZE;
            bz -= 1;
        }
    }

    Block *bl = findBlock(bx, by, bz);
    if (!bl)
        bl = addBlock(bx, by, bz);

    int cx = ox;
    int cy = oy;
    int cz = oz;

    if (gx > 0) {
        cx = gx - bx * BLOCK_SIZE;
    }
    if (gy > 0) {
        cy = gy - by * BLOCK_SIZE;
    }
    if (gz > 0) {
        cz = gz - bz * BLOCK_SIZE;
    }


    Cube &cu = bl->cubes[Pos((1 + cx), (1 + cy), (1 + cz))];
    cu.xyz = glm::vec3(cx, cy, cz);
    if (cu.t != 0) {
        cu.t = 0;
        bl->cubeNum--;
        if (bl->cubeNum == 0) {
            this->delBlock(bl);
        }
    }
    return 0;
}

bool isTransparent(char t) {
    if (t == 0)
        return true;
    if (t == 2)
        return true;
    return false;
}

static const float positions[6][4][3] = {
        {{-1, -1, -1}, {-1, -1, +1}, {-1, +1, -1}, {-1, +1, +1}},
        {{+1, -1, -1}, {+1, -1, +1}, {+1, +1, -1}, {+1, +1, +1}},
        {{-1, +1, -1}, {-1, +1, +1}, {+1, +1, -1}, {+1, +1, +1}},
        {{-1, -1, -1}, {-1, -1, +1}, {+1, -1, -1}, {+1, -1, +1}},
        {{-1, -1, -1}, {-1, +1, -1}, {+1, -1, -1}, {+1, +1, -1}},
        {{-1, -1, +1}, {-1, +1, +1}, {+1, -1, +1}, {+1, +1, +1}}
};
static const float normals[6][3] = {
        {-1, 0,  0},
        {+1, 0,  0},
        {0,  +1, 0},
        {0,  -1, 0},
        {0,  0,  -1},
        {0,  0,  +1}
};
static const float uvs[6][4][2] = {
        {{0, 0}, {1, 0}, {0, 1}, {1, 1}},
        {{1, 0}, {0, 0}, {1, 1}, {0, 1}},
        {{0, 1}, {0, 0}, {1, 1}, {1, 0}},
        {{0, 0}, {0, 1}, {1, 0}, {1, 1}},
        {{0, 0}, {0, 1}, {1, 0}, {1, 1}},
        {{1, 0}, {1, 1}, {0, 0}, {0, 1}}
};
static const float indices[6][6] = {
        {0, 3, 2, 0, 1, 3},
        {0, 3, 1, 0, 2, 3},
        {0, 3, 2, 0, 1, 3},
        {0, 3, 1, 0, 2, 3},
        {0, 3, 2, 0, 1, 3},
        {0, 3, 1, 0, 2, 3}
};
static const float flipped[6][6] = {
        {0, 1, 2, 1, 3, 2},
        {0, 2, 1, 2, 3, 1},
        {0, 1, 2, 1, 3, 2},
        {0, 2, 1, 2, 3, 1},
        {0, 1, 2, 1, 3, 2},
        {0, 2, 1, 2, 3, 1}
};

int Block::delBuffer() {
    glDeleteVertexArrays(1, &this->VAO);
    glDeleteVertexArrays(1, &this->VAO2);
    glDeleteBuffers(1, &this->VBO);
    return 0;
}

//int Block::BuildBlockVerticesTask(WorkQueue &inputQueue) {
//    Block *bl = new Block();
//    *bl = *this;
//    inputQueue.enqueue(bl);
//    return 0;
//}

int Block::init(int bx, int by, int bz) {

    auto &bl = *this;
    Cube cu;
    cu.xyz = glm::vec3(0.0f);
    cu.t = 0;

    glm::vec3 blPos(bx, by, bz);
#if defined(T_1)
    bl.cubes = std::vector<Cube>((Terrain::BLOCK_SIZE2) * (Terrain::BLOCK_SIZE2) * (Terrain::BLOCK_SIZE2),
                                 cu);
#else
    for(int mx = 0; mx < (2 + Terrain::BLOCK_SIZE2) ;mx++)
        for(int my = 0; my < (2 + Terrain::BLOCK_SIZE2) ;my++)
            for(int mz = 0; mz < (2 + Terrain::BLOCK_SIZE2) ;mz++)
            {
                bl.cubes[Pos(mx, my, mz)] = cu;
            }
#endif
    bl.xyz = glm::vec3(bx, by, bz);
    bl.faceNum = 0;
    bl.VBO = 0;
    bl.VAO = 0;
    bl.VAO2 = 0;
    bl.cubeNum = 0;
    return 0;
}


int Block::buildBlockVertices() {
    int faces = 0;

    for (int x = 0; x < BLOCK_SIZE; x++)
        for (int y = 0; y < BLOCK_SIZE; y++)
            for (int z = 0; z < BLOCK_SIZE; z++) {
                if (this->cubes[Pos((1 + x), (1 + y), (1 + z))].t == 0)
                    continue;
                int left = isTransparent(this->cubes[Pos((1 + x - 1), (1 + y), (1 + z))].t);//l
                int right = isTransparent(this->cubes[Pos((1 + x + 1), (1 + y), (1 + z))].t);//r
                int bottom = isTransparent(this->cubes[Pos((1 + x), (1 + y - 1), (1 + z))].t);//d
                int top = isTransparent(this->cubes[Pos((1 + x), (1 + y + 1), (1 + z))].t);//t
                int back = isTransparent(this->cubes[Pos((1 + x), (1 + y), (1 + z - 1))].t);//b
                int front = isTransparent(this->cubes[Pos((1 + x), (1 + y), (1 + z + 1))].t);//f
                int total = left + right + bottom + top + back + front;
                if (total == 0) {
                    continue;
                }
                faces += total;
            }

    this->faceNum = faces;
    this->vertices = std::vector<GLfloat>(sizeof(GLfloat) * 6 * GLARR * faces, 0);
    float *d = this->vertices.data();
    for (int x = 0; x < BLOCK_SIZE; x++)
        for (int y = 0; y < BLOCK_SIZE; y++)
            for (int z = 0; z < BLOCK_SIZE; z++) {

                if (this->cubes[Pos((1 + x), (1 + y), (1 + z))].t == 0)
                    continue;


                int left = isTransparent(this->cubes[Pos((1 + x - 1), (1 + y), (1 + z))].t);//l
                int right = isTransparent(this->cubes[Pos((1 + x + 1), (1 + y), (1 + z))].t);//r
                int bottom = isTransparent(this->cubes[Pos((1 + x), (1 + y - 1), (1 + z))].t);//d
                int top = isTransparent(this->cubes[Pos((1 + x), (1 + y + 1), (1 + z))].t);//t
                int back= isTransparent(this->cubes[Pos((1 + x), (1 + y), (1 + z - 1))].t);//b
                int front = isTransparent(this->cubes[Pos((1 + x), (1 + y), (1 + z + 1))].t);//f
                int total = left + right + bottom + top + back + front;
                if (total == 0) {
                    continue;
                }

                static const int lookup3[6][4][3] = {
                        {{0,  1,  3},  {2,  1,  5},  {6,  3,  7},  {8,  5,  7}},
                        {{18, 19, 21}, {20, 19, 23}, {24, 21, 25}, {26, 23, 25}},
                        {{6,  7,  15}, {8,  7,  17}, {24, 15, 25}, {26, 17, 25}},
                        {{0,  1,  9},  {2,  1,  11}, {18, 9,  19}, {20, 11, 19}},
                        {{0,  3,  9},  {6,  3,  15}, {18, 9,  21}, {24, 15, 21}},
                        {{2,  5,  11}, {8,  5,  17}, {20, 11, 23}, {26, 17, 23}}
                };
                static const int lookup4[6][4][4] = {
                        {{0,  1,  3,  4},  {1,  2,  4,  5},  {3,  4,  6,  7},  {4,  5,  7,  8}},
                        {{18, 19, 21, 22}, {19, 20, 22, 23}, {21, 22, 24, 25}, {22, 23, 25, 26}},
                        {{6,  7,  15, 16}, {7,  8,  16, 17}, {15, 16, 24, 25}, {16, 17, 25, 26}},
                        {{0,  1,  9,  10}, {1,  2,  10, 11}, {9,  10, 18, 19}, {10, 11, 19, 20}},
                        {{0,  3,  9,  12}, {3,  6,  12, 15}, {9,  12, 18, 21}, {12, 15, 21, 24}},
                        {{2,  5,  11, 14}, {5,  8,  14, 17}, {11, 14, 20, 23}, {14, 17, 23, 26}}
                };
                static const float curve[4] = {0.0, 0.25, 0.5, 0.75};
                int faces[6] = {left, right, top, bottom, back, front};
#if 1
                float ao[6][4];
                memset(ao, 0, sizeof(ao));

                char neighbors[27] = {0};
                char lights[27] = {0};
                float shades[27] = {0};
                int index = 0;
                for (int dx = -1; dx <= 1; dx++) {
                    for (int dy = -1; dy <= 1; dy++) {
                        for (int dz = -1; dz <= 1; dz++) {
                            neighbors[index] = this->cubes[XYZ(1 + x + dx, 1 + y + dy, 1 + z + dz)].t;

                            index++;
                        }
                    }
                }

                {

                    for (int i = 0; i < 6; i++) {
                        if (faces[i] == 0)
                            continue;
                        for (int j = 0; j < 4; j++) {
                            int corner = neighbors[lookup3[i][j][0]];
                            int side1 = neighbors[lookup3[i][j][1]];
                            int side2 = neighbors[lookup3[i][j][2]];
                            int value = side1 && side2 ? 3 : corner + side1 + side2;
                            float shade_sum = 0;

                            for (int k = 0; k < 4; k++) {
                                shade_sum += shades[lookup4[i][j][k]];

                            }
                            float total = curve[value] + shade_sum / 4.0;
                            ao[i][j] = std::min<float>(total, 1.0);


                        }
                    }


                }
#endif


                for (int i = 0; i < 6; i++) {
                    if (faces[i] == 0)
                        continue;
                    int flip = ao[i][0] + ao[i][3] > ao[i][1] + ao[i][2];
                    for (int v = 0; v < 6; v++) {
                        int j = flip ? flipped[i][v] : indices[i][v];
                        float offX = 0.5;
                        float offY = 0.5;
                        float offZ = 0.5;

                        float vxx = offX + (this->xyz.x * BLOCK_SIZE) + x + (positions[i][j][0]) * 0.5;
                        float vxy = offY + (this->xyz.y * BLOCK_SIZE) + y + (positions[i][j][1]) * 0.5;
                        float vxz = offZ + (this->xyz.z * BLOCK_SIZE) + z + (positions[i][j][2]) * 0.5;
                        *(d++) = vxx;
                        *(d++) = vxy;
                        *(d++) = vxz;


                        *(d++) = 0 + normals[i][0];
                        *(d++) = 0 + normals[i][1];
                        *(d++) = 0 + normals[i][2];

                        if (i == 5 || i == 4) {
                            float u1 = (uvs[i][j][0]);
                            *(d++) = 1 - u1;
                            float v1 = (uvs[i][j][1]);
                            *(d++) = v1;
                        } else {
                            float u1 = (uvs[i][j][0]);
                            *(d++) = u1;
                            float v1 = (uvs[i][j][1]);
                            *(d++) = v1;
                        }

                        *(d++) = i;
                        *(d++) = 0.3 + (1.0 - ao[i][j]) * 0.7;

                    }
                }
            }


    return 0;
}

int Block::BindBuffer() {
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);

    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);

    glBufferData(GL_ARRAY_BUFFER, this->vertices.size() * sizeof(float), this->vertices.data(), GL_STATIC_DRAW);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    glGenVertexArrays(1, &VAO2);
    return 0;
}

int Block::makeTerrain() {
    auto *bl = this;
    int bx = this->xyz.x;
    int by = this->xyz.y;
    int bz = this->xyz.z;

    for (int cx = 0; cx < BLOCK_SIZE; cx++) {
        for (int cz = 0; cz < BLOCK_SIZE; cz++) {
            int flag = 1;
            if (cx == 0 || cz == 0 || cx > BLOCK_SIZE || cz > BLOCK_SIZE) {
                flag = -1;
            }

            int gcx = bx * BLOCK_SIZE + cx;
            int gcz = bz * BLOCK_SIZE + cz;
            float f = simplex2(gcx * 0.01, gcz * 0.01, 4, 0.5, 2);
            float g = simplex2(-gcx * 0.01, -gcz * 0.01, 2, 0.9, 2);
            int mh = g * 32 + 16;
            int h = f * mh;
            int w = 1;
            int t = 1;
            if (h <= t) {
                h = t;
                w = 2;
            }
            h = std::min(h, (int) BLOCK_SIZE);
            // sand and grass terrain
            for (int cy = 0; cy < h; cy++) {
                //map_set(map, x, y, z, w);
                //func(cx, cy, cz, w * flag, arg);

                Cube &cu = bl->cubes[Pos((1 + cx), (1 + cy), (1 + cz))];
                cu.xyz = glm::vec3(cx, cy, cz);
                cu.t = 1;

            }

//            if (w == 1) {
//                if (SHOW_PLANTS) {
//                    // grass
//                    if (simplex2(-x * 0.1, z * 0.1, 4, 0.8, 2) > 0.6) {
//                        func(x, h, z, 17 * flag, arg);
//                    }
//                    // flowers
//                    if (simplex2(x * 0.05, -z * 0.05, 4, 0.8, 2) > 0.7) {
//                        int w = 18 + simplex2(x * 0.1, z * 0.1, 4, 0.8, 2) * 7;
//                        func(x, h, z, w * flag, arg);
//                    }
//                }
//                // trees
//                int ok = SHOW_TREES;
//                if (dx - 4 < 0 || dz - 4 < 0 ||
//                    dx + 4 >= BLOCK_SIZE || dz + 4 >= BLOCK_SIZE)
//                {
//                    ok = 0;
//                }
//                if (ok && simplex2(x, z, 6, 0.5, 2) > 0.84) {
//                    for (int y = h + 3; y < h + 8; y++) {
//                        for (int ox = -3; ox <= 3; ox++) {
//                            for (int oz = -3; oz <= 3; oz++) {
//                                int d = (ox * ox) + (oz * oz) +
//                                        (y - (h + 4)) * (y - (h + 4));
//                                if (d < 11) {
//                                    func(x + ox, y, z + oz, 15, arg);
//                                }
//                            }
//                        }
//                    }
//                    for (int y = h; y < h + 7; y++) {
//                        func(x, y, z, 5, arg);
//                    }
//                }
//            }
//            // clouds
//            if (SHOW_CLOUDS) {
//                for (int y = 64; y < 72; y++) {
//                    if (simplex3(
//                            x * 0.01, y * 0.1, z * 0.01, 8, 0.5, 2) > 0.75)
//                    {
//                        func(x, y, z, 16 * flag, arg);
//                    }
//                }
//            }
        }
    }
    return 0;
}

Block *World::makeTerrain(float gx, float gy, float gz) {
    int pad = 1;
    int bx = gx / BLOCK_SIZE;
    int by = gy / BLOCK_SIZE;
    int bz = gz / BLOCK_SIZE;
    int ox = 0;
    int oy = 0;
    int oz = 0;
    if (gx < 0) {
        ox = gx - bx * BLOCK_SIZE;
        if (ox != 0) {
            ox += BLOCK_SIZE;
            bx -= 1;
        }
    }
    if (gy < 0) {
        oy = gy - by * BLOCK_SIZE;
        if (oy != 0) {
            oy += BLOCK_SIZE;
            by -= 1;
        }
    }
    if (gz < 0) {
        oz = gz - bz * BLOCK_SIZE;
        if (oz != 0) {
            oz += BLOCK_SIZE;
            bz -= 1;
        }
    }
    auto *bl = findBlockByPos(gx, gy, gz);

    if (bl == nullptr) {
        bl = addBlock(bx, by, bz);
    }
    for (int cx = 0; cx < BLOCK_SIZE; cx++) {
        for (int cz = 0; cz < BLOCK_SIZE; cz++) {
            int flag = 1;
            if (cx == 0 || cz == 0 || cx > BLOCK_SIZE || cz > BLOCK_SIZE) {
                flag = -1;
            }

            int gcx = bx * BLOCK_SIZE + cx;
            int gcz = bz * BLOCK_SIZE + cz;

            float f = simplex2(gcx * 0.01, gcz * 0.01, 4, 0.9, 2);
            float g = simplex2(-gcx * 0.01, -gcz * 0.01, 2, 0.9, 2);
            int mh = g * 32 + 8;
            int h = f * mh + 0;
            int w = 1;
            int t = 1;
            int h2 = h;
            if (h <= mh) {
                h = t;
                w = 2;
            }

            h2 = std::min(h2 - (by) * BLOCK_SIZE, (int) BLOCK_SIZE);

            // sand and grass terrain
            for (int cy = 0; cy < h2; cy++) {
                //map_set(map, x, y, z, w);
                //func(cx, cy, cz, w * flag, arg);

                Cube &cu = bl->cubes[Pos((1 + cx), (1 + cy), (1 + cz))];
                cu.xyz = glm::vec3(cx, cy, cz);
                cu.t = 1;
                bl->cubeNum++;

            }

//            if (w == 1) {
//                if (SHOW_PLANTS) {
//                    // grass
//                    if (simplex2(-x * 0.1, z * 0.1, 4, 0.8, 2) > 0.6) {
//                        func(x, h, z, 17 * flag, arg);
//                    }
//                    // flowers
//                    if (simplex2(x * 0.05, -z * 0.05, 4, 0.8, 2) > 0.7) {
//                        int w = 18 + simplex2(x * 0.1, z * 0.1, 4, 0.8, 2) * 7;
//                        func(x, h, z, w * flag, arg);
//                    }
//                }
//                // trees
//                int ok = SHOW_TREES;
//                if (dx - 4 < 0 || dz - 4 < 0 ||
//                    dx + 4 >= BLOCK_SIZE || dz + 4 >= BLOCK_SIZE)
//                {
//                    ok = 0;
//                }
//                if (ok && simplex2(x, z, 6, 0.5, 2) > 0.84) {
//                    for (int y = h + 3; y < h + 8; y++) {
//                        for (int ox = -3; ox <= 3; ox++) {
//                            for (int oz = -3; oz <= 3; oz++) {
//                                int d = (ox * ox) + (oz * oz) +
//                                        (y - (h + 4)) * (y - (h + 4));
//                                if (d < 11) {
//                                    func(x + ox, y, z + oz, 15, arg);
//                                }
//                            }
//                        }
//                    }
//                    for (int y = h; y < h + 7; y++) {
//                        func(x, y, z, 5, arg);
//                    }
//                }
//            }
//            // clouds
//            if (SHOW_CLOUDS) {
//                for (int y = 64; y < 72; y++) {
//                    if (simplex3(
//                            x * 0.01, y * 0.1, z * 0.01, 8, 0.5, 2) > 0.75)
//                    {
//                        func(x, y, z, 16 * flag, arg);
//                    }
//                }
//            }
        }
    }
    return bl;
}

Block *World::makePlane(float gx, float gy, float gz) {
    int pad = 1;
    int bx = gx / BLOCK_SIZE;
    int by = gy / BLOCK_SIZE;
    int bz = gz / BLOCK_SIZE;
    int ox = 0;
    int oy = 0;
    int oz = 0;
    if (gx < 0) {
        ox = gx - bx * BLOCK_SIZE;
        if (ox != 0) {
            ox += BLOCK_SIZE;
            bx -= 1;
        }
    }
    if (gy < 0) {
        oy = gy - by * BLOCK_SIZE;
        if (oy != 0) {
            oy += BLOCK_SIZE;
            by -= 1;
        }
    }
    if (gz < 0) {
        oz = gz - bz * BLOCK_SIZE;
        if (oz != 0) {
            oz += BLOCK_SIZE;
            bz -= 1;
        }
    }
    auto *bl = findBlockByPos(gx, gy, gz);

    if (bl == nullptr) {
        bl = addBlock(bx, by, bz);
    }
    for (int cx = 0; cx < BLOCK_SIZE; cx++) {
        for (int cz = 0; cz < BLOCK_SIZE; cz++) {
            int flag = 1;
            if (cx == 0 || cz == 0 || cx > BLOCK_SIZE || cz > BLOCK_SIZE) {
                flag = -1;
            }

            int gcx = bx * BLOCK_SIZE + cx;
            int gcz = bz * BLOCK_SIZE + cz;

            float f = simplex2(gcx * 0.01, gcz * 0.01, 4, 0.9, 2);
            float g = simplex2(-gcx * 0.01, -gcz * 0.01, 2, 0.9, 2);
            int mh = g * 32 + 8;
            int h = f * mh + 0;
            int w = 1;
            int t = 1;
            int h2 = h;
            if (h <= mh) {
                h = t;
                w = 2;
            }

            h2 = std::min(h2 - (by) * BLOCK_SIZE, (int) BLOCK_SIZE);

            // sand and grass terrain
            for (int cy = 0; cy < 1; cy++) {
                //map_set(map, x, y, z, w);
                //func(cx, cy, cz, w * flag, arg);

                Cube &cu = bl->cubes[Pos((1 + cx), (1 + cy), (1 + cz))];
                cu.xyz = glm::vec3(cx, cy, cz);
                cu.t = 1;
                bl->cubeNum++;

            }

//            if (w == 1) {
//                if (SHOW_PLANTS) {
//                    // grass
//                    if (simplex2(-x * 0.1, z * 0.1, 4, 0.8, 2) > 0.6) {
//                        func(x, h, z, 17 * flag, arg);
//                    }
//                    // flowers
//                    if (simplex2(x * 0.05, -z * 0.05, 4, 0.8, 2) > 0.7) {
//                        int w = 18 + simplex2(x * 0.1, z * 0.1, 4, 0.8, 2) * 7;
//                        func(x, h, z, w * flag, arg);
//                    }
//                }
//                // trees
//                int ok = SHOW_TREES;
//                if (dx - 4 < 0 || dz - 4 < 0 ||
//                    dx + 4 >= BLOCK_SIZE || dz + 4 >= BLOCK_SIZE)
//                {
//                    ok = 0;
//                }
//                if (ok && simplex2(x, z, 6, 0.5, 2) > 0.84) {
//                    for (int y = h + 3; y < h + 8; y++) {
//                        for (int ox = -3; ox <= 3; ox++) {
//                            for (int oz = -3; oz <= 3; oz++) {
//                                int d = (ox * ox) + (oz * oz) +
//                                        (y - (h + 4)) * (y - (h + 4));
//                                if (d < 11) {
//                                    func(x + ox, y, z + oz, 15, arg);
//                                }
//                            }
//                        }
//                    }
//                    for (int y = h; y < h + 7; y++) {
//                        func(x, y, z, 5, arg);
//                    }
//                }
//            }
//            // clouds
//            if (SHOW_CLOUDS) {
//                for (int y = 64; y < 72; y++) {
//                    if (simplex3(
//                            x * 0.01, y * 0.1, z * 0.01, 8, 0.5, 2) > 0.75)
//                    {
//                        func(x, y, z, 16 * flag, arg);
//                    }
//                }
//            }
        }
    }
    return bl;
}

Block *World::makeFixedPlane(float gx, float gy, float gz, int mx, int my, int mz) {
    int pad = 1;
    int bx = gx / BLOCK_SIZE;
    int by = gy / BLOCK_SIZE;
    int bz = gz / BLOCK_SIZE;
    int ox = 0;
    int oy = 0;
    int oz = 0;
    if (gx < 0) {
        ox = gx - bx * BLOCK_SIZE;
        if (ox != 0) {
            ox += BLOCK_SIZE;
            bx -= 1;
        }
    }
    if (gy < 0) {
        oy = gy - by * BLOCK_SIZE;
        if (oy != 0) {
            oy += BLOCK_SIZE;
            by -= 1;
        }
    }
    if (gz < 0) {
        oz = gz - bz * BLOCK_SIZE;
        if (oz != 0) {
            oz += BLOCK_SIZE;
            bz -= 1;
        }
    }
    auto *bl = findBlockByPos(gx, gy, gz);

    if (bl == nullptr) {
        bl = addBlock(bx, by, bz);
    }
    for (int cx = 0; cx < std::min<int>(mx,BLOCK_SIZE); cx++) {

        for (int cz = 0; cz < std::min<int>(mz, BLOCK_SIZE); cz++) {
            int flag = 1;
            if (cx == 0 || cz == 0 || cx > BLOCK_SIZE || cz > BLOCK_SIZE) {
                flag = -1;
            }

            int gcx = bx * BLOCK_SIZE + cx;
            int gcz = bz * BLOCK_SIZE + cz;

            float f = simplex2(gcx * 0.01, gcz * 0.01, 4, 0.9, 2);
            float g = simplex2(-gcx * 0.01, -gcz * 0.01, 2, 0.9, 2);
            int mh = g * 32 + 8;
            int h = f * mh + 0;
            int w = 1;
            int t = 1;
            int h2 = h;
            if (h <= mh) {
                h = t;
                w = 2;
            }

            h2 = std::min(h2 - (by) * BLOCK_SIZE, (int) BLOCK_SIZE);

            // sand and grass terrain
            for (int cy = 0; cy < 1; cy++) {
                //map_set(map, x, y, z, w);
                //func(cx, cy, cz, w * flag, arg);

                Cube &cu = bl->cubes[Pos((1 + cx), (1 + cy), (1 + cz))];
                cu.xyz = glm::vec3(cx, cy, cz);
                cu.t = 1;
                bl->cubeNum++;

            }
//            for (int cy = 1; cy < 2; cy++) {
//                //map_set(map, x, y, z, w);
//                //func(cx, cy, cz, w * flag, arg);
//
//                if(map1[cx][cz] == 1)
//                {
//                    Cube &cu = bl->cubes[Pos((1 + cx), (1 + cy), (1 + cz))];
//                    cu.xyz = glm::vec3(cx, cy, cz);
//                    cu.t = 1;
//                    bl->cubeNum++;
//                }
//
//
//            }
//            if (w == 1) {
//                if (SHOW_PLANTS) {
//                    // grass
//                    if (simplex2(-x * 0.1, z * 0.1, 4, 0.8, 2) > 0.6) {
//                        func(x, h, z, 17 * flag, arg);
//                    }
//                    // flowers
//                    if (simplex2(x * 0.05, -z * 0.05, 4, 0.8, 2) > 0.7) {
//                        int w = 18 + simplex2(x * 0.1, z * 0.1, 4, 0.8, 2) * 7;
//                        func(x, h, z, w * flag, arg);
//                    }
//                }
//                // trees
//                int ok = SHOW_TREES;
//                if (dx - 4 < 0 || dz - 4 < 0 ||
//                    dx + 4 >= BLOCK_SIZE || dz + 4 >= BLOCK_SIZE)
//                {
//                    ok = 0;
//                }
//                if (ok && simplex2(x, z, 6, 0.5, 2) > 0.84) {
//                    for (int y = h + 3; y < h + 8; y++) {
//                        for (int ox = -3; ox <= 3; ox++) {
//                            for (int oz = -3; oz <= 3; oz++) {
//                                int d = (ox * ox) + (oz * oz) +
//                                        (y - (h + 4)) * (y - (h + 4));
//                                if (d < 11) {
//                                    func(x + ox, y, z + oz, 15, arg);
//                                }
//                            }
//                        }
//                    }
//                    for (int y = h; y < h + 7; y++) {
//                        func(x, y, z, 5, arg);
//                    }
//                }
//            }
//            // clouds
//            if (SHOW_CLOUDS) {
//                for (int y = 64; y < 72; y++) {
//                    if (simplex3(
//                            x * 0.01, y * 0.1, z * 0.01, 8, 0.5, 2) > 0.75)
//                    {
//                        func(x, y, z, 16 * flag, arg);
//                    }
//                }
//            }
        }
    }
    return bl;
}