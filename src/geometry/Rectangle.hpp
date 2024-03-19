#ifndef RECTANGLE_HH
#define RECTANGLE_HH


#include "../shader/Shader.hpp"
#include <vector>
#include "../include/glm/vec3.hpp"

class Rectangle {

private:
    GLuint VAO, VBO, EBO;
    std::vector<glm::vec3> vertices;
    std::vector<GLuint> indices;

public:
    Rectangle();
    Rectangle(glm::vec3 a, glm::vec3 b, glm::vec3 c, glm::vec3 d);
    ~Rectangle();
    void init();
    void draw(Shader shader) const;
};

#endif