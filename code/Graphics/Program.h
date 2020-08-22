#pragma once


#include "Config.h"

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <vector>

#include <vector>
#include <map>
#include <string>


namespace Simple2D
{
    class Color {
    public:
        float r, g, b, a;

    public:
        Color() : r(0), g(0), b(0), a(0) {}

        Color(float nr, float ng, float nb, float na) : r(nr), g(ng), b(nb), a(na) {}

        //Color(int nr, int ng, int nb, int na) : r(nr / 255.0), g(ng / 255.0), b(nb / 255.0), a(na / 255.0) {}

        void set(float nr, float ng, float nb, float na) {
            r = nr;
            g = ng;
            b = nb;
            a = na;
        }
    };

    inline Color operator+(const Color &color, const Color &o) {
        return Color(color.r + o.r, color.g + o.g, color.b + o.b, color.a + o.a);
    }

    inline Color operator+(const Color &color, float f) {
        return Color(color.r + f, color.g + f, color.b + f, color.a + f);
    }

    inline Color operator-(const Color &color, const Color &o) {
        return Color(color.r - o.r, color.g - o.g, color.b - o.b, color.a - o.a);
    }

    inline Color operator-(const Color &color, float f) {
        return Color(color.r - f, color.g - f, color.b - f, color.a - f);
    }

    inline Color operator*(const Color &color, const Color &o) {
        return Color(color.r * o.r, color.g * o.g, color.b * o.b, color.a * o.a);
    }

    inline Color operator*(const Color &color, float f) {
        return Color(color.r * f, color.g * f, color.b * f, color.a * f);
    }

    inline Color operator/(const Color &color, const Color &o) {
        return Color(color.r / o.r, color.g / o.g, color.b / o.b, color.a / o.a);
    }

    inline Color operator/(const Color &color, float f) {
        return Color(color.r / f, color.g / f, color.b / f, color.a / f);
    }


    enum UniformType
    {
        UT_1IV,
        UT_1FV,
        UT_2IV,
        UT_2FV,
        UT_3IV,
        UT_3FV,
        UT_4IV,
        UT_4FV,	/* 0 - 7 */

        UT_1I,
        UT_1F,
        UT_2I,
        UT_2F,
        UT_3I,
        UT_3F,
        UT_4I,
        UT_4F,	/* 8 - 15 */

        UT_MATRIX3,
        UT_MATRIX4,

        UT_TEXTURE
    };

    //-----------------------------------------------------------------------------
    // Uniform
    //-----------------------------------------------------------------------------
    class Uniform
    {
    public:
        Uniform() : nLocation(-1), v(nullptr) {}
        Uniform(int location) : nLocation(location), v(nullptr) {}

        ~Uniform() { if ( v != nullptr ) delete[] v; }

        void SetValueI(int v0)
        {
            this->SetUniformType(UT_1I);
            v[0] = v0;
        }

        void SetValueI(int v0, int v1)
        {
            this->SetUniformType(UT_2I);
            v[0] = v0; v[1] = v1;
        }

        void SetValueI(int v0, int v1, int v2)
        {
            this->SetUniformType(UT_3I);
            v[0] = v0; v[1] = v1; v[2] = v2;
        }

        void SetValueI(int v0, int v1, int v2, int v3)
        {
            this->SetUniformType(UT_4I);
            v[0] = v0; v[1] = v1; v[2] = v2; v[3] = v3;
        }

        void SetValueF(float v0)
        {
            this->SetUniformType(UT_1F);
            v[0] = v0;
        }

        void SetValueF(float v0, float v1)
        {
            this->SetUniformType(UT_2F);
            v[0] = v0; v[1] = v1;
        }

        void SetValueF(float v0, float v1, float v2)
        {
            this->SetUniformType(UT_3F);
            v[0] = v0; v[1] = v1; v[2] = v2;
        }

        void SetValueF(float v0, float v1, float v2, float v3)
        {
            this->SetUniformType(UT_4F);
            v[0] = v0; v[1] = v1; v[2] = v2; v[3] = v3;
        }

        void SetUniformIV(int count, int* values)
        {
            nCount = count;

            UniformType ut = ( UniformType ) ((nCount - 1) * 2);
            this->SetUniformType(ut);
            memcpy(v, values, sizeof( int ) * nCount);
        }

        void SetUniformFV(int count, float* values)
        {
            nCount = count;

            UniformType ut = ( UniformType ) (nCount * 2 - 1);
            this->SetUniformType(ut);
            memcpy(v, values, sizeof( float ) * nCount);
        }

        void SetTexture(int texture_id)
        {
            this->SetUniformType(UT_TEXTURE);
            v[0] = texture_id;
        }

        void SetMatrix3(float* values, bool transpose = true)
        {
            bTranspose = transpose;
            this->SetUniformType(UT_MATRIX3);
            memcpy(v, values, sizeof( float ) * 12);
        }

        void SetMatrix4(float* values, bool transpose = true)
        {
            bTranspose = transpose;
            this->SetUniformType(UT_MATRIX4);
            memcpy(v, values, sizeof( float ) * 16);
        }

        void SetUniformType(UniformType ut)
        {
            if ( uniformType == ut ) return;
            if ( v ) delete[] v;

            int size = 0;
            uniformType = ut;

            switch ( uniformType ) {
                case UniformType::UT_TEXTURE:
                case UniformType::UT_1I:
                case UniformType::UT_1F:  size = 1; break;
                case UniformType::UT_2I:
                case UniformType::UT_2F:  size = 2; break;
                case UniformType::UT_3I:
                case UniformType::UT_3F:  size = 3; break;
                case UniformType::UT_4I:
                case UniformType::UT_4F:  size = 4; break;
                case UniformType::UT_1IV:
                case UniformType::UT_1FV: size = nCount * 1; break;
                case UniformType::UT_2IV:
                case UniformType::UT_2FV: size = nCount * 2; break;
                case UniformType::UT_3IV:
                case UniformType::UT_3FV: size = nCount * 3; break;
                case UniformType::UT_4IV:
                case UniformType::UT_4FV: size = nCount * 4; break;

                case UniformType::UT_MATRIX3: size = 12; break;
                case UniformType::UT_MATRIX4: size = 16; break;
            }
            v = new GLfloat[size];
        }

        bool Bind()
        {
            switch ( uniformType ) {
                case UniformType::UT_1I: glUniform1i(nLocation, v[0]); break;
                case UniformType::UT_1F: glUniform1f(nLocation, v[0]); break;
                case UniformType::UT_2I: glUniform2i(nLocation, v[0], v[1]); break;
                case UniformType::UT_2F: glUniform2f(nLocation, v[0], v[1]); break;
                case UniformType::UT_3I: glUniform3i(nLocation, v[0], v[1], v[2]); break;
                case UniformType::UT_3F: glUniform3f(nLocation, v[0], v[1], v[2]); break;
                case UniformType::UT_4I: glUniform4i(nLocation, v[0], v[1], v[2], v[3]); break;
                case UniformType::UT_4F: glUniform4f(nLocation, v[0], v[1], v[2], v[3]); break;
                case UniformType::UT_1IV: glUniform1iv(nLocation, nCount, ( GLint* ) v); break;
                case UniformType::UT_1FV: glUniform1fv(nLocation, nCount, ( GLfloat* ) v); break;
                case UniformType::UT_2IV: glUniform2iv(nLocation, nCount, ( GLint* ) v); break;
                case UniformType::UT_2FV: glUniform2fv(nLocation, nCount, ( GLfloat* ) v); break;
                case UniformType::UT_3IV: glUniform3iv(nLocation, nCount, ( GLint* ) v); break;
                case UniformType::UT_3FV: glUniform3fv(nLocation, nCount, ( GLfloat* ) v); break;
                case UniformType::UT_4IV: glUniform4iv(nLocation, nCount, ( GLint* ) v); break;
                case UniformType::UT_4FV: glUniform4fv(nLocation, nCount, ( GLfloat* ) v); break;
                case UniformType::UT_MATRIX3: glUniformMatrix3fv(nLocation, 1, bTranspose ? GL_TRUE : GL_FALSE, v); break;
                case UniformType::UT_MATRIX4: glUniformMatrix4fv(nLocation, 1, bTranspose ? GL_TRUE : GL_FALSE, v); break;
                case UniformType::UT_TEXTURE:
                    glActiveTexture(GL_TEXTURE0);
                    glBindTexture(GL_TEXTURE_2D, v[0]);
                    glUniform1i(nLocation, 0);
                    return true;
            }
            return false;
        }

    private:
        int nLocation;
        GLfloat* v;

        int nCount;
        bool bTranspose;

        UniformType uniformType;
    };


    //-----------------------------------------------------------------------------
    // UniformBlock
    //-----------------------------------------------------------------------------
    class UniformBlockBase {
    public:
        virtual ~UniformBlockBase() {}
        virtual int GetBindingPoint() = 0;
    };


    template<class T>
    class UniformBlock : public UniformBlockBase
    {
    public:
        UniformBlock(int binding_point)
        {
            memset(data, 0, sizeof(T));

            glGenBuffers(1, &buffer);
            glBindBuffer(GL_UNIFORM_BUFFER, buffer);
            glBufferData(GL_UNIFORM_BUFFER, sizeof(T), data, GL_STATIC_DRAW);
            glBindBuffer(GL_UNIFORM_BUFFER, 0);

            this->BindToBindingPoints(binding_point);
        }

        ~UniformBlock()
        {
            glDeleteBuffers(1, &buffer);
        }

        void UpdateData()
        {
            this->UpdateData(0, sizeof(T));
        }

        void UpdateData(int offset, int size)
        {
            glBindBuffer(GL_UNIFORM_BUFFER, buffer);
            glBufferSubData(GL_UNIFORM_BUFFER, offset, size, data);
            glBindBuffer(GL_UNIFORM_BUFFER, 0);
        }

        void UpdateData(int offset, int size, void* new_data)
        {
            memcpy(data + offset, new_data, size);

            glBindBuffer(GL_UNIFORM_BUFFER, buffer);
            glBufferSubData(GL_UNIFORM_BUFFER, offset, size, new_data);
            glBindBuffer(GL_UNIFORM_BUFFER, 0);
        }

        void BindToBindingPoints(int binding_point)
        {
            nBindingPoint = binding_point;
            glBindBufferBase(GL_UNIFORM_BUFFER, nBindingPoint, buffer);
        }

        int GetBindingPoint()
        {
            return nBindingPoint;
        }



        char* Data()
        {
            return data;
        }

    private:
        char data[sizeof(T)];

        GLuint buffer;
        int nBindingPoint;
    };


    //-----------------------------------------------------------------------------
    // Shader
    //-----------------------------------------------------------------------------
    enum ShaderType
    {
        Shader_Vertex,
        Shader_Geometry,
        Shader_Fragment
    };

    class Program
    {
        struct VertexAttribute
        {
            int layout;
            int size;
            int type;
            int stride;
            int offset;
        };

    public:
        Program();
        ~Program();

        /* 设置顶点属性 */
        template<class Type>
        void SetVertexAttributes(int location, glm::vec2* offset)
        {
            SetVertexAttribute(location, 2, GL_FLOAT, ( long long ) offset, sizeof(Type));
        }

        template<class Type>
        void SetVertexAttributes(int location, glm::vec3* offset)
        {
            SetVertexAttribute(location, 3, GL_FLOAT, ( long long ) offset, sizeof(Type));
        }

        template<class Type>
        void SetVertexAttributes(int location, Color* offset)
        {
            SetVertexAttribute(location, 4, GL_FLOAT, ( long long ) offset, sizeof(Type));
        }

        template<class Type>
        void SetVertexAttributes(int location, int* offset)
        {
            SetVertexAttribute(location, 1, GL_INT, ( long long ) offset, sizeof(Type));
        }

        template<class Type>
        void SetVertexAttributes(int location, float* offset)
        {
            SetVertexAttribute(location, 1, GL_FLOAT, ( long long ) offset, sizeof(Type));
        }

        void SetVertexAttribute(int location, int size, int type, int offset, int stride);

        void AttachShader(GLuint shader);

        void LinkProgram();

        void ConnectToUniformBlock(UniformBlockBase* uniform_block, const char* uniform_name);

        void BindProgram();

        void BindVertexDataToGPU(void* data);

        Uniform* NewUniformByName(const char* name);

        bool HasVertexAttributes() { return nVertexAttributeCount != 0; }

        GLuint GetProgramID() { return program; }

        static Program* CreateProgram(const char* vname, const char* fname, const char* gname = nullptr);

        static Program* CreateProgramWithSource(const char* vsource, const char* fsource, const char* gsource = nullptr);

        static GLuint CreateShader(const char* name, ShaderType type);

        static GLuint CreateShaderWithSource(const char* source, ShaderType type);
    private:
        GLuint program;

        GLuint vShaders[3];
        int nShaderCount;

        /* 顶点属性 */
        static const int max_vertex_attribute = 8;
        VertexAttribute vertexAttributes[max_vertex_attribute];
        int nVertexAttributeCount;
    };


    //-----------------------------------------------------------------------------
    // ProgramEffect
    //-----------------------------------------------------------------------------
    class ProgramEffect
    {
    public:
        ProgramEffect(Program* program) : pProgram(program) {}

        ~ProgramEffect() { Clear(); }

        Uniform* GetUniform(const std::string& name)
        {
            auto it = mUniformTable.find(name);

            if ( it == mUniformTable.end() ) {
                Uniform* uniform = pProgram->NewUniformByName(name.c_str());
                mUniformTable.insert(std::make_pair(name, uniform));
                return uniform;
            }
            return it->second;
        }

        void BindUniforms()
        {
            for ( auto& ele : mUniformTable ) ele.second->Bind();
        }

        void Clear()
        {
            for ( auto& ele : mUniformTable ) delete ele.second;
            mUniformTable.clear();
        }

        Program* GetProgram() { return pProgram; }

    private:
        Program* pProgram;
        std::map<std::string, Uniform*> mUniformTable;
    };
}
