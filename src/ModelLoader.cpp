#include "../include/ModelLoader.hpp"

ModelLoader::ModelLoader() {
}

ModelLoader::~ModelLoader() {
}

bool ModelLoader::load(const char* path, std::vector<vec3>& outVertices, std::vector<GLuint>& outIndices, std::vector<vec3>& outNormals) {
    std::ifstream modelFile {path};
    if(!modelFile.is_open()) {
        std::cerr << "ERROR::MODELLOADER::FAILED_TO_OPEN_FILE" << std::endl;
        return false;
    }

    std::string line;
    while (std::getline(modelFile, line)) {
        std::istringstream iss {line};
        std::string token;
        iss >> token;

        if (token == "v") {
            vec3 vertex;
            iss >> vertex.x() >> vertex.y() >> vertex.z();
            outVertices.push_back(vertex);
        } else if (token == "vn") {
            vec3 normals;
            iss >> normals.x() >> normals.y() >> normals.z();
            outNormals.push_back(normals);
        } else if (token == "f") {
            std::string indices;
            while (iss >> indices) {
                std::istringstream viss(indices);
                std::string indexStr;
                getline(viss, indexStr, '/');
                int index = std::stoi(indexStr) - 1; // -1 because indices in obj files starts at 1
                outIndices.push_back(index);
            }
        }
    }

    modelFile.close();
    return true;
}
