#include "utils/ModelLoader.hpp"

ModelLoader::ModelLoader(std::string path) : path {path} {
}

ModelLoader::~ModelLoader() {
}

void ModelLoader::load() {
    std::ifstream modelFile {path};
    std::string line;

    if(modelFile.is_open()) {
        while (std::getline(modelFile, line)) {
            char type {line.at(0)};
            if (type == 'v') {
                glm::vec3 vec = parseLineToVertexVector(line.substr(2, line.length()));
                Vertex vertex;
                vertex.position = vec;
                vertex.color = glm::vec3 {0.8, 0.0, 0.0};
                vertices.push_back(vertex);
            } else if (type == 'f') {
                glm::uvec3 vec = parseLineToFaceVector(line.substr(2, line.length()));
                faces.push_back(vec.x);
                faces.push_back(vec.y);
                faces.push_back(vec.z);
            } 
        }

        modelFile.close();
    } else {
        std::cerr << "ERROR::MODELLODER::LOAD::FAILED TO OPEN FILE" << std::endl;
    }
}

glm::vec3 ModelLoader::parseLineToVertexVector(std::string line) {
    glm::vec3 vec;
    sscanf(line.c_str(), "%f %f %f", &(vec.x), &(vec.y), &(vec.z));
    return vec;
}

glm::uvec3 ModelLoader::parseLineToFaceVector(std::string line) {
    glm::uvec3 vec;
    sscanf(line.c_str(), "%u %*c %u %*c %u", &(vec.x), &(vec.y), &(vec.z));
    return vec;
}

std::vector<Vertex> ModelLoader::getVertices() {
    return vertices;
}

std::vector<GLuint> ModelLoader::getFaces() {
    return faces;
}