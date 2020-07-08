//
// Created by caspasex on 2019/10/17.
//

#pragma once
#ifndef SHADER_
#define SHADER_

#include "Config.h"

#include <glad/glad.h>
#include <glm/glm.hpp>

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

class Shader {
public:
    unsigned int ID;

    Shader(const GLchar *vertexPath, const GLchar *fragmentPath) {
        std::string vertexCode;
        std::string fragmentCode;
        std::string geometryCode;
        //std::string tessControlCode;
        //std::string tessEvalCode;
        std::ifstream vShaderFile;
        std::ifstream fShaderFile;
        std::ifstream gShaderFile;
        std::ifstream tcShaderFile;
        std::ifstream teShaderFile;
        vShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
        fShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
        gShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
        tcShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
        teShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
        try {
            vShaderFile.open(vertexPath);
            fShaderFile.open(fragmentPath);
            std::stringstream vShaderStream, fShaderStream;
            vShaderStream << vShaderFile.rdbuf();
            fShaderStream << fShaderFile.rdbuf();
            vShaderFile.close();
            fShaderFile.close();
            vertexCode = vShaderStream.str();
            fragmentCode = fShaderStream.str();
        }
        catch (std::ifstream::failure &e) {
            std::cout << "shader err: FILE READ" << std::endl;
        }
        const char *vShaderCode = vertexCode.c_str();
        const char *fShaderCode = fragmentCode.c_str();

        GLuint vertex, fragment;
        vertex = glCreateShader(GL_VERTEX_SHADER);
        glShaderSource(vertex, 1, &vShaderCode, nullptr);
        glCompileShader(vertex);
        checkCompileErrors(vertex, vertexPath);


        fragment = glCreateShader(GL_FRAGMENT_SHADER);
        glShaderSource(fragment, 1, &fShaderCode, nullptr);
        glCompileShader(fragment);
        checkCompileErrors(fragment, fragmentPath);




        ID = glCreateProgram();
        glAttachShader(ID, vertex);
        glAttachShader(ID, fragment);

        glLinkProgram(ID);
        checkCompileErrors(ID, "PROGRAM");

        glDeleteShader(vertex);
        glDeleteShader(fragment);
    }

    void use() {
        glUseProgram(ID);
    }

    void del() {
        glDeleteProgram(ID);
    }

    void setBool(const std::string &name, bool value) const {
        int l = glGetUniformLocation(ID, name.c_str());
        if (l == -1)
            std::cout << name << std::endl;
        //assert(l != -1);
        glUniform1i(glGetUniformLocation(ID, name.c_str()), (int) value);
    }

    void setInt(const std::string &name, int value) const {
        int l = glGetUniformLocation(ID, name.c_str());
        if (l == -1)
            std::cout << name << std::endl;
        //assert(l != -1);
        glUniform1i(glGetUniformLocation(ID, name.c_str()), value);
    }

    void setFloat(const std::string &name, float value) const {
        int l = glGetUniformLocation(ID, name.c_str());
        if (l == -1)
            std::cout << name << std::endl;
        //assert(l != -1);
        glUniform1f(l, value);

    }

    void setVec2(const std::string &name, const glm::vec2 &value) const {
        int l = glGetUniformLocation(ID, name.c_str());
        if (l == -1)
            std::cout << name << std::endl;
        //assert(l != -1);
        glUniform2fv(glGetUniformLocation(ID, name.c_str()), 1, &value[0]);
    }

    void setVec2(const std::string &name, float x, float y) const {
        int l = glGetUniformLocation(ID, name.c_str());
        if (l == -1)
            std::cout << name << std::endl;
        //assert(l != -1);
        glUniform2f(glGetUniformLocation(ID, name.c_str()), x, y);
    }

    void setVec3(const std::string &name, const glm::vec3 &value) const {
        int l = glGetUniformLocation(ID, name.c_str());
        if (l == -1)
            std::cout << name << std::endl;
        //assert(l != -1);
        glUniform3fv(glGetUniformLocation(ID, name.c_str()), 1, &value[0]);
    }

    void setVec3(const std::string &name, float x, float y, float z) const {
        int l = glGetUniformLocation(ID, name.c_str());//TODO 这里需要优化掉,初始化获取Location
        if (l == -1)
            std::cout << name << std::endl;
        //assert(l != -1);
        glUniform3f(glGetUniformLocation(ID, name.c_str()), x, y, z);
    }

    void setVec4(const std::string &name, const glm::vec4 &value) const {
        int l = glGetUniformLocation(ID, name.c_str());
        if (l == -1)
            std::cout << name << std::endl;
        //assert(l != -1);
        glUniform4fv(glGetUniformLocation(ID, name.c_str()), 1, &value[0]);
    }

    void setVec4(const std::string &name, float x, float y, float z, float w) {
        int l = glGetUniformLocation(ID, name.c_str());
        if (l == -1)
            std::cout << name << std::endl;
        //assert(l != -1);
        glUniform4f(glGetUniformLocation(ID, name.c_str()), x, y, z, w);
    }

    void setMat4(const std::string &name, const glm::mat4 &mat) const {
        int l = glGetUniformLocation(ID, name.c_str());
        if (l == -1)
            std::cout << name << std::endl;
        //assert(l != -1);
        glUniformMatrix4fv(glGetUniformLocation(ID, name.c_str()), 1, GL_FALSE, &mat[0][0]);
    }

    void setMat4Transpose(const std::string &name, const glm::mat4 &mat) const {
        int l = glGetUniformLocation(ID, name.c_str());
        if (l == -1)
            std::cout << name << std::endl;
        //assert(l != -1);
        glUniformMatrix4fv(glGetUniformLocation(ID, name.c_str()), 1, GL_TRUE, &mat[0][0]);
    }

private:

    static void checkCompileErrors(GLuint shader, const std::string &type) {
        GLint success;
        GLchar infoLog[1024];
        if (type != "PROGRAM") {
            glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
            if (!success) {
                glGetShaderInfoLog(shader, 1024, nullptr, infoLog);
                std::cout << "ERROR::SHADER_COMPILATION: " << type << "\n" << infoLog << std::endl;
            }
        } else {
            glGetProgramiv(shader, GL_LINK_STATUS, &success);
            if (!success) {
                glGetProgramInfoLog(shader, 1024, nullptr, infoLog);
                std::cout << "ERROR::PROGRAM_LINKING_ERROR: " << type << "\n" << infoLog << std::endl;
            }
        }
    }
};


#endif