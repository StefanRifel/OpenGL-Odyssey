#ifndef MODELLODER_HH
#define MODELLODER_HH

#include <string>
#include <vector>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <fstream>
#include <iostream>
#include <sstream>

#include "../libs/SMath/include/vec3.hpp"

/*
    This class is responsible for loading .obj files and convert its content to:
    - v = vertex
    - vt = texture coordinate of one vertex (not implemented yet)
    - vn  = normal of one vertex
    - f = face (set of 3 indices that represent a triangle)
*/
class ModelLoader {

private:

public:
    ModelLoader();
    static bool load(const char* path, std::vector<vec3>& outVertices, std::vector<GLuint>& outIndices, std::vector<vec3>& normals);
    
    ~ModelLoader();
};

#endif