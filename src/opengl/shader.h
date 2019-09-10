// Shader Loader took from https://learnopengl.com

#pragma once
#ifndef SHADER_H
#define SHADER_H

#include <glad/glad.h>

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
class Shader
{
    public:
        Shader(const char* vertexPath, const char* fragmentPath)
        {
            std::string vertexCode;
            std::string fragmentCode;
            std::ifstream vShaderFile;
            std::ifstream fShaderFile;
         
            vShaderFile.exceptions (std::ifstream::failbit | std::ifstream::badbit);
            fShaderFile.exceptions (std::ifstream::failbit | std::ifstream::badbit);
            try 
            {
                vShaderFile.open(vertexPath);
                fShaderFile.open(fragmentPath);
                std::stringstream vShaderStream, fShaderStream;
                
                vShaderStream << vShaderFile.rdbuf();
                fShaderStream << fShaderFile.rdbuf();
                
                vShaderFile.close();
                fShaderFile.close();
                
                vertexCode   = vShaderStream.str();
                fragmentCode = fShaderStream.str();
            }
            catch (std::ifstream::failure e)
            {
                std::cout << "ERROR::SHADER::FILE_NOT_SUCCESFULLY_READ" << std::endl;
            }

            const char* vShaderCode = vertexCode.c_str();
            const char * fShaderCode = fragmentCode.c_str();
            
            unsigned int vertex, fragment;

            vertex = glCreateShader(GL_VERTEX_SHADER);
            glShaderSource(vertex, 1, &vShaderCode, NULL);
            glCompileShader(vertex);
            checkCompileErrors(vertex, "VERTEX");

            fragment = glCreateShader(GL_FRAGMENT_SHADER);
            glShaderSource(fragment, 1, &fShaderCode, NULL);
            glCompileShader(fragment);
            checkCompileErrors(fragment, "FRAGMENT");

            ID = glCreateProgram();
            glAttachShader(ID, vertex);
            glAttachShader(ID, fragment);
            glLinkProgram(ID);
            checkCompileErrors(ID, "PROGRAM");
            
            glDeleteShader(vertex);
            glDeleteShader(fragment);
        }
        
        void use() 
        { 
            glUseProgram(ID); 
        }
        
        void setBool(const std::string &name, bool value)
        {         
            int location = glGetUniformLocation(ID, name.c_str());
            glUseProgram(ID); 
            glUniform1i(location, (int)value); 
        }
        
        void setInt(const std::string &name, int value)
        { 
            int location = glGetUniformLocation(ID, name.c_str());
            glUseProgram(ID); 
            glUniform1i(location, value); 
        }
        
        void setFloat(const std::string &name, float value)
        { 
            int location = glGetUniformLocation(ID, name.c_str());
            glUseProgram(ID); 
            glUniform1f(location, value); 
        }

        void setVec4(const std::string &name, float value1, float value2, float value3, float value4)
        {
            int location = glGetUniformLocation(ID, name.c_str());
            glUseProgram(ID); 
            glUniform4f(location, value1, value2, value3, value4);
        }
        
        unsigned int ID;

    private:
        void checkCompileErrors(unsigned int shader, std::string type)
        {
            int success;
            char infoLog[1024];
            if (type != "PROGRAM")
            {
                glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
                if (!success)
                {
                    glGetShaderInfoLog(shader, 1024, NULL, infoLog);
                    std::cout << "ERROR::SHADER_COMPILATION_ERROR of type: " << type << "\n" << infoLog << "\n -- --------------------------------------------------- -- " << std::endl;
                }
            }
            else
            {
                glGetProgramiv(shader, GL_LINK_STATUS, &success);
                if (!success)
                {
                    glGetProgramInfoLog(shader, 1024, NULL, infoLog);
                    std::cout << "ERROR::PROGRAM_LINKING_ERROR of type: " << type << "\n" << infoLog << "\n -- --------------------------------------------------- -- " << std::endl;
                }
            }
        }
};
#endif

