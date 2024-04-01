#ifndef TRIANGLE_STRIP_HH
#define TRIANGLE_STRIP_HH

#include "../shader/Shader.hpp"
#include <vector>
#include "../include/glm/vec3.hpp"

class TriangleStrip {

private:
    GLuint VAO, PVBO, CVBO, EBO;
    std::vector<glm::vec3> vertices;
    std::vector<glm::vec3> color;
    std::vector<GLuint> indices;

public:
    TriangleStrip();
    TriangleStrip(std::vector<glm::vec3> verticies, std::vector<glm::vec3> color, std::vector<GLuint> indices);
    void init();
    void draw(Shader shader) const;
};

#endif