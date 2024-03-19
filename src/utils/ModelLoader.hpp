#ifndef MODELLODER_HH
#define MODELLODER_HH

#include <string>
#include <vector>

#include "../include/glm/vec3.hpp"

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <fstream>
#include <iostream>
#include <sstream>

class ModelLoader {

private:
    std::string path;
    std::vector<glm::vec3> vertices;
    std::vector<glm::uvec3> faces;

public:
    ModelLoader(std::string path);
    void load();
    static glm::vec3 parseLineToVertexVector(std::string line);
    static glm::uvec3 parseLineToFaceVector(std::string line);

    std::vector<glm::vec3> getVertices();
    std::vector<glm::uvec3> getFaces();
    
    ~ModelLoader();
};

#endif