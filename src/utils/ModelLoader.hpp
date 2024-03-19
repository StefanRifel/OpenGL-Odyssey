#ifndef MODELLODER_HH
#define MODELLODER_HH

#include <string>
#include <vector>

#include "../include/glm/vec3.hpp"

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "../geometry/Vertex.h"

#include <fstream>
#include <iostream>
#include <sstream>

class ModelLoader {

private:
    std::string path;
    std::vector<Vertex> vertices;
    std::vector<GLuint> faces;

public:
    ModelLoader(std::string path);
    void load();
    static glm::vec3 parseLineToVertexVector(std::string line);
    static glm::uvec3 parseLineToFaceVector(std::string line);

    std::vector<Vertex> getVertices();
    std::vector<GLuint> getFaces();
    
    ~ModelLoader();
};

#endif