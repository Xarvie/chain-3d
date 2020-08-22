#include "Program.h"
#include "Renderer.h"

#include <string>
#include <fstream>
#include <sstream>

namespace Simple2D
{
    Program::Program() : program(-1)
    {
        nVertexAttributeCount = 0;
        memset(vertexAttributes, 0, sizeof(vertexAttributes));

        nShaderCount = vShaders[0] = vShaders[1] = vShaders[2] = 0;

        program = glCreateProgram();
    }

    Program::~Program()
    {
        glDeleteProgram(program);
        for ( int i = 0; i < nShaderCount; i++ ) {
            glDeleteShader(vShaders[i]);
        }
    }

    void Program::SetVertexAttribute(int location, int size, int type, int offset, int stride)
    {
        vertexAttributes[location].layout = location;
        vertexAttributes[location].size = size;
        vertexAttributes[location].type = type;
        vertexAttributes[location].stride = stride;
        vertexAttributes[location].offset = offset;

        if ( nVertexAttributeCount <= location ) {
            nVertexAttributeCount = location + 1;
        }
    }

    void Program::AttachShader(GLuint shader)
    {
        glAttachShader(program, shader);
        vShaders[nShaderCount++] = shader;
    }

    void Program::LinkProgram()
    {
        glLinkProgram(program);

        GLint success;
        glGetProgramiv(program, GL_COMPILE_STATUS, &success);

        if ( !success ) {
            GLchar error_info[512];
            glGetProgramInfoLog(program, 512, NULL, error_info);
            //assert(LOG_WRITE_DEBUG("着色程序链接错误！： %s", error_info));
        }
    }

    void Program::BindProgram()
    {
        glUseProgram(program);
    }

    void Program::ConnectToUniformBlock(UniformBlockBase* uniform_block, const char* uniform_name)
    {
        GLuint index = glGetUniformBlockIndex(program, uniform_name);
        glUniformBlockBinding(program, index, uniform_block->GetBindingPoint());
    }

    Uniform* Program::NewUniformByName(const char* name)
    {
        int location = glGetUniformLocation(program, name);
        if ( location == -1 ) {
            //LOG_WRITE_DEBUG("不存在的 uniform 变量 %s", name);
            assert(location != -1);
        }
        return new Uniform(location);
    }

    void Program::BindVertexDataToGPU(void* data)
    {
        void* data_offset = nullptr;
        for ( int i = 0; i < nVertexAttributeCount; i++ ) {
            data_offset = static_cast< char* > ( data ) + vertexAttributes[i].offset;

            /* 上传顶点数据 */
            glVertexAttribPointer(
                    vertexAttributes[i].layout,
                    vertexAttributes[i].size,
                    vertexAttributes[i].type,
                    GL_FALSE,
                    vertexAttributes[i].stride,
                    data_offset);

            glEnableVertexAttribArray(vertexAttributes[i].layout);
        }
    }

    Program* Program::CreateProgram(const char* vname, const char* fname, const char* gname)
    {
        Program* program = new Program;
        program->AttachShader(CreateShader(vname, ShaderType::Shader_Vertex));
        program->AttachShader(CreateShader(fname, ShaderType::Shader_Fragment));
        if ( gname ) program->AttachShader(CreateShader(gname, ShaderType::Shader_Geometry));

        program->LinkProgram();
        return program;
    }

    Program* Program::CreateProgramWithSource(const char* vsource, const char* fsource, const char* gsource)
    {
        Program* program = new Program;
        program->AttachShader(CreateShaderWithSource(vsource, ShaderType::Shader_Vertex));
        program->AttachShader(CreateShaderWithSource(fsource, ShaderType::Shader_Fragment));
        if ( gsource ) program->AttachShader(CreateShaderWithSource(gsource, ShaderType::Shader_Geometry));

        program->LinkProgram();
        return program;
    }

    GLuint Program::CreateShader(const char* name, ShaderType type)
    {
        std::string source;
        std::ifstream file;

        file.open(std::string(SHADER_DIR)+(name), std::ios::in);
        if ( file.is_open() == false ) {
            //assert(LOG_WRITE_DEBUG("不存在的着色程序文件：%s", name));
        }

        std::stringstream stream;
        stream << file.rdbuf();
        source = stream.str();
        file.close();

        return CreateShaderWithSource(source.c_str(), type);
    }

    GLuint Program::CreateShaderWithSource(const char* source, ShaderType type)
    {
        static GLuint map[] = {
                GL_VERTEX_SHADER,
                GL_GEOMETRY_SHADER,
                GL_FRAGMENT_SHADER
        };

        GLuint shader = glCreateShader(map[type]);
        glShaderSource(shader, 1, &source, NULL);
        glCompileShader(shader);

        GLint success;
        glGetShaderiv(shader, GL_COMPILE_STATUS, &success);

        if ( !success ) {
            GLchar error_info[512];
            glGetShaderInfoLog(shader, 512, NULL, error_info);
            //assert(LOG_WRITE_DEBUG("着色程序编译错误！： %s", error_info));
        }
        return shader;
    }
}