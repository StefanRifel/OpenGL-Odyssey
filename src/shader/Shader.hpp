#ifndef SHADER_HH
#define SHADER_HH

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "../utils/Logger.hpp"

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

class Shader {
public:
    // the program ID
    GLuint ID;
    
    // constructor reads and builds the shader
    Shader(const char* vertexPath, const char* fragmentPath);
    Shader();

    void createShader(const char* vertexPath, const char* fragmentPath);
    // use/activate the shader
    void use();
    // utility uniform functions
    void setBool(const std::string &name, bool value) const;
    void setInt(const std::string &name, int value) const;
    void setFloat(const std::string &name, float value) const;
};

#endif