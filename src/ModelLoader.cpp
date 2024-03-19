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
                vertices.push_back(parseLineToVertexVector(line.substr(2, line.length())));
            } else if (type == 'f') {
                faces.push_back(parseLineToFaceVector(line.substr(2, line.length())));
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

std::vector<glm::vec3> ModelLoader::getVertices() {
    return vertices;
}

std::vector<glm::uvec3> ModelLoader::getFaces() {
    return faces;
}