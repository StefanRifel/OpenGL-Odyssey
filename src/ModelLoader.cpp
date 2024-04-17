#include "utils/ModelLoader.hpp"

ModelLoader::ModelLoader() {
}

ModelLoader::~ModelLoader() {
}

bool ModelLoader::load(const char* path, std::vector<Vertex>& outVertices, std::vector<GLuint>& outFaces) {
    std::ifstream modelFile {path};
    std::string line;

    if(modelFile.is_open()) {
        int escape = 0;
        while (std::getline(modelFile, line)) {
            std::stringstream test {line};
            std::string token;
            getline(test, token, ' ');
            if (token.at(0) == 'v' && token.size() <= 1) {
                Vertex vertex;
                sscanf((line.substr(2, line.length())).c_str(), "%f %f %f", &(vertex.position.x), &(vertex.position.y), &(vertex.position.z));
                outVertices.push_back(vertex);
            } else if (token.at(0) == 'f' && token.size() <= 1) {
                std::string token;
                std::stringstream ss {line.substr(2, line.length())};
                while (getline(ss, token, ' ')) {
                    // calculate -1 because indices in obj files starts at 1 and we need to start at 0
                    outFaces.push_back(token.at(0) - '0' - 1);
                }
            }
        }
        modelFile.close();
    } else {
        return false;
    }
    return true;
}

glm::uvec3 ModelLoader::parseLineToFaceVector(std::string line) {
    glm::uvec3 vec;
    
    return vec;
}
