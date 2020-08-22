//
// Created by caspase on 8/20/2020.
//

#include "TextureMgr.h"



#include "tinyxml2.h"

#include "stb_image.h"

#include <iostream>

namespace Simple2D
{
    //------------------------------------------------------------------
    // TextureUnique
    //------------------------------------------------------------------
    TextureUnique::TextureUnique(const char* filename) : id(-1), width(0), height(0)
    {
        glGenTextures(1, &id);
        glBindTexture(GL_TEXTURE_2D, id);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

        glBindTexture(GL_TEXTURE_2D, 0);

        if ( filename ) {
            this->SetImageData(filename);
        }
    }

    TextureUnique::~TextureUnique()
    {
        glDeleteTextures(1, &id);
    }

    void TextureUnique::SetWrapping(TexWrapping wraps, TexWrapping wrapt)
    {
        static GLint revert[Wrapping_Count] = {
                GL_REPEAT,
                GL_MIRRORED_REPEAT,
                GL_CLAMP_TO_EDGE,
                GL_CLAMP_TO_BORDER,
        };

        glBindTexture(GL_TEXTURE_2D, id);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, revert[wrapt]);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, revert[wraps]);
        glBindTexture(GL_TEXTURE_2D, 0);
    }

    bool TextureUnique::SetImageData(const std::string& filename)
    {
        std::string fullName = std::string(RES_DIR) + filename;

        unsigned char* image_data = nullptr;



        {
            int w = 0, h = 0;
            int  nrComponents;
            stbi_set_flip_vertically_on_load(true);
            unsigned char* image_data = stbi_load(fullName.c_str(), &w, &h, &nrComponents, 0);
            if (image_data) {

                GLenum dataFormat;
                if (nrComponents == 1) {
                    dataFormat = GL_RED;
                }
                else if (nrComponents == 3) {
                    dataFormat = GL_RGB;
                }
                else if (nrComponents == 4) {
                    dataFormat = GL_RGBA;
                }

                this->SetImageData(w, h, image_data, dataFormat == GL_RGBA);
                stbi_image_free(image_data);
            }
            else {
                std::cout << "err: load texture: " << fullName << std::endl;
            }
        }




        return true;
    }

    void TextureUnique::SetImageData(int width, int height, void* data, bool has_alpha)
    {
        format = has_alpha ? GL_RGBA : GL_RGB;

        glBindTexture(GL_TEXTURE_2D, id);
        glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
        glBindTexture(GL_TEXTURE_2D, 0);

        this->width = width;
        this->height = height;
    }

    void TextureUnique::UpdateImageData(int xoffset, int yoffset, int width, int height, void* data)
    {
        glBindTexture(GL_TEXTURE_2D, id);
        glTexSubImage2D(GL_TEXTURE_2D, 0, xoffset, yoffset, width, height, format, GL_UNSIGNED_BYTE, data);
        glBindTexture(GL_TEXTURE_2D, 0);
    }


    //------------------------------------------------------------------
    // TexturePool
    //------------------------------------------------------------------
    TexturePool::TexturePool()
    {
        /* 初始化 FreeImage */
        //FreeImage_Initialise(TRUE);
    }

    TexturePool::~TexturePool()
    {
        for ( auto& ele : vTextureUniqpeList ) delete ele;
        vTextureUniqpeList.clear();

        for ( auto& ele : vTextureMap ) delete ele.second;
        vTextureMap.clear();
    }

    TexturePool* TexturePool::GetInstance()
    {
        static TexturePool texture_pool;
        return &texture_pool;
    }

    Texture2D* TexturePool::GetTexture(const std::string& filename)
    {
        Texture2D* texture_2d = nullptr;

        auto it = vTextureMap.find(filename);
        if ( it == vTextureMap.end() ) {
            TextureUnique* texture_unique = new TextureUnique(filename.c_str());

            texture_2d = new Texture2D;
            texture_2d->textureUnique = texture_unique;
            texture_2d->width  = texture_unique->width;
            texture_2d->height = texture_unique->height;

            texture_2d->uv[0] = glm::vec2(0, 0);
            texture_2d->uv[1] = glm::vec2(0, 1);
            texture_2d->uv[2] = glm::vec2(1, 1);
            texture_2d->uv[3] = glm::vec2(1, 0);

            vTextureMap.insert(std::make_pair(filename, texture_2d));
        }
        else {
            texture_2d = it->second;
        }
        return texture_2d;
    }

    bool TexturePool::LoadFileFromPlist(const std::string& filename)
    {
        std::vector<PlistParseData> ppd_list;
        if ( ParsePlistFile(filename, ppd_list) == false ) {
            //LOG_WRITE("解析文件 %s 失败！", filename.c_str());
            return false;
        }

        TextureUnique* texture_unique = new TextureUnique(ppd_list.back().filename.c_str());

        for ( int i = 0; i < ppd_list.size() - 1; i++ ) {
            PlistParseData& ppd = ppd_list[i];

            Texture2D* texture_2d = new Texture2D;
            texture_2d->textureUnique = texture_unique;
            texture_2d->width = ppd.width;
            texture_2d->height = ppd.height;

            /* 计算纹理坐标 */
            glm::vec2 p1, p2;
            if ( ppd.rotate ) {
                p1.x = ( float ) ppd.offsetx / texture_unique->width;
                p1.y = 1 - ( float ) (ppd.offsety + ppd.width) / texture_unique->height;

                p2.x = ( float ) (ppd.offsetx + ppd.height) / texture_unique->width;
                p2.y = 1 - ( float ) ppd.offsety / texture_unique->height;

                texture_2d->uv[3] = glm::vec2(p1.x, p1.y);
                texture_2d->uv[0] = glm::vec2(p1.x, p2.y);
                texture_2d->uv[1] = glm::vec2(p2.x, p2.y);
                texture_2d->uv[2] = glm::vec2(p2.x, p1.y);
            }
            else {
                p1.x = ( float ) ppd.offsetx / texture_unique->width;
                p1.y = 1- ( float ) (ppd.offsety + ppd.height) / texture_unique->height;

                p2.x = ( float ) (ppd.offsetx + ppd.width) / texture_unique->width;
                p2.y = 1- ( float ) ppd.offsety / texture_unique->height;

                texture_2d->uv[0] = glm::vec2(p1.x, p1.y);
                texture_2d->uv[1] = glm::vec2(p1.x, p2.y);
                texture_2d->uv[2] = glm::vec2(p2.x, p2.y);
                texture_2d->uv[3] = glm::vec2(p2.x, p1.y);
            }
            vTextureMap.insert(std::make_pair(ppd.filename, texture_2d));
        }
        return true;
    }

    bool TexturePool::ParsePlistFile(const std::string& filename, std::vector<PlistParseData>& ppd_list)
    {
        tinyxml2::XMLDocument doc;

        auto path = std::string(RES_DIR) + filename;
        if ( doc.LoadFile(path.c_str()) != tinyxml2::XML_NO_ERROR ) {
            //LOG_WRITE_DEBUG("不存在 plist 文件：%s", filename.c_str());
            return false;
        }

        tinyxml2::XMLElement* frame_ele = nullptr;
        tinyxml2::XMLElement* context_ele = nullptr;

        tinyxml2::XMLNode* plist_node = doc.RootElement();

        plist_node = plist_node->FirstChildElement();
        frame_ele = plist_node->FirstChildElement();

        tinyxml2::XMLElement* begin_node = frame_ele->NextSiblingElement()->FirstChildElement();

        std::string left, right;

        while ( begin_node ) {
            PlistParseData ppd;

            ppd.filename = begin_node->GetText();
            context_ele = begin_node->NextSiblingElement();

            context_ele = context_ele->FirstChildElement("string");
            std::string size = context_ele->GetText();

            /* {{xx, xx},{xx, xx}} */
            left = size.substr(2, size.find_first_of("}") - 2);
            right = left.substr(left.find_first_of(",") + 1, left.size() - left.find_first_of(","));
            left = left.substr(0, left.find_first_of(","));

            ppd.offsetx = atoi(left.c_str());
            ppd.offsety = atoi(right.c_str());

            right = size.substr(size.find_last_of("{") + 1, size.size() - size.find_last_of("{") - 3);
            left = right.substr(0, right.find_first_of(","));
            right = right.substr(right.find_first_of(",") + 1, right.size() - right.find_first_of(","));

            ppd.width = atoi(left.c_str());
            ppd.height = atoi(right.c_str());

            context_ele = context_ele->NextSiblingElement();
            context_ele = context_ele->NextSiblingElement();
            context_ele = context_ele->NextSiblingElement();
            context_ele = context_ele->NextSiblingElement();

            std::string rotate = context_ele->Name();
            ppd.rotate = (rotate.compare("true") == 0);

            begin_node = begin_node->NextSiblingElement();
            begin_node = begin_node->NextSiblingElement();

            ppd_list.push_back(ppd);
        }
        /* 获取图像文件名 */
        frame_ele = frame_ele->NextSiblingElement();
        frame_ele = frame_ele->NextSiblingElement();
        frame_ele = frame_ele->NextSiblingElement();

        tinyxml2::XMLElement* metadata = frame_ele->FirstChildElement("string");
        std::string texture_name = metadata->GetText();

        metadata = metadata->NextSiblingElement("string");
        std::string texture_size = metadata->GetText();

        int dot = texture_size.find_first_of(",");

        PlistParseData ppd;
        ppd.filename = texture_name;
        ppd.width	 = atoi(texture_size.substr(1, dot - 1).c_str());
        ppd.height	 = atoi(texture_size.substr(dot + 1, texture_size.size() - dot - 2).c_str());

        ppd_list.push_back(ppd);
        return true;
    }
}