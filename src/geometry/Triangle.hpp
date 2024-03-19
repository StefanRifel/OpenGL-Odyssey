#ifndef TRIANGLE_HH
#define TRIANGLE_HH


#include "../shader/Shader.hpp"
#include <vector>
#include "../include/glm/vec3.hpp"

class Triangle {

private:
    GLuint VAO, VBO;
    std::vector<glm::vec3> vertices;

public:
    Triangle();
    Triangle(glm::vec3 a, glm::vec3 b, glm::vec3 c);
    ~Triangle();
    void init();
    void draw(Shader shader) const;
};

#endif