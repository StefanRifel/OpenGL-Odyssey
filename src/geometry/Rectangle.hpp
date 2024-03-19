#ifndef RECTANGLE_HH
#define RECTANGLE_HH


#include "../shader/Shader.hpp"
#include <vector>
#include "../include/glm/vec3.hpp"

enum FileFormat {jpg = GL_RGB, png = GL_RGBA};

class Rectangle {

private:
    GLuint VAO, VBO, EBO;
    std::vector<glm::vec3> vertices;
    std::vector<GLuint> indices;
    GLuint texture1;
    GLuint texture2;

public:
    Rectangle();
    Rectangle(glm::vec3 a, glm::vec3 b, glm::vec3 c, glm::vec3 d);
    ~Rectangle();
    void init();
    void draw(Shader shader) const;
    void loadTexture(const char* texturePath, GLuint& texture, FileFormat format);
};

#endif