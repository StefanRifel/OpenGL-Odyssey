#ifndef RECTANGLESHADEREXPERIMENT_HH
#define RECTANGLESHADEREXPERIMENT_HH

#include "../shader/Shader.hpp"
#include <vector>
#include "../include/glm/vec3.hpp"

class RectangleShaderExperiment {

private:
    GLuint VAO, PVBO, VVBO, EBO;
    std::vector<glm::vec3> vertices;
    std::vector<GLfloat> vertValue;
    std::vector<GLuint> indices;

public:
    RectangleShaderExperiment();
    RectangleShaderExperiment(std::vector<glm::vec3> verticies, std::vector<GLfloat> vertValue, std::vector<GLuint> indices);
    void init();
    void draw(Shader shader) const;
};

#endif