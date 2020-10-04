//
// Created by caspase on 8/20/2020.
//

#ifndef INC_3D_TEXTUREMGR_H
#define INC_3D_TEXTUREMGR_H


class TextureMgr {

};
#include <Config.h>
#include <map>
#include <vector>
#include <string>

#include <glad/glad.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#define TEXTURE_BINDING_NAME "defaultTexture"

namespace Simple2D
{
    enum TexWrapping
    {
        Wrapping_Repeat,
        Wrapping_MirroredRepeat,
        Wrapping_ToEdge,
        Wrapping_ToBorder,
        Wrapping_Count
    };

    //------------------------------------------------------------------
    // TextureUnique
    //------------------------------------------------------------------
    class TextureUnique
    {
    public:
        TextureUnique(const char* filename = nullptr);

        ~TextureUnique();

        void SetWrapping(TexWrapping wraps = Wrapping_ToEdge, TexWrapping wrapt = Wrapping_ToEdge);

        bool SetImageData(const std::string& filename);

        void SetImageData(int width, int height, void* data, bool has_alpha = true);

        void UpdateImageData(int xoffset, int yoffset, int width, int height, void* data);

    public:
        int width;
        int height;

        GLuint id;
        GLuint format;
    };


    struct Texture2D
    {
        TextureUnique* textureUnique;

        int	 width;
        int	 height;
        glm::vec2 uv[4];
    };

    //------------------------------------------------------------------
    // TexturePool
    //------------------------------------------------------------------
    class Pass;
    class Program;

    class TexturePool
    {
    private:
        struct PlistParseData
        {
            std::string filename;
            bool rotate;

            int offsetx;
            int offsety;

            int width;
            int height;
        };

        TexturePool();
        ~TexturePool();

    public:
        static TexturePool* GetInstance();

        Texture2D* GetTexture(const std::string& filename);

        bool LoadFileFromPlist(const std::string& filename);

    private:
        bool ParsePlistFile(const std::string& filename, std::vector<PlistParseData>& ppd);

    private:
        std::vector<TextureUnique*> vTextureUniqpeList;
        std::map<std::string, Texture2D*> vTextureMap;
    };
}

#endif //INC_3D_TEXTUREMGR_H
