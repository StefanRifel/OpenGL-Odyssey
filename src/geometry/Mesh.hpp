#ifndef MESH_HH
#define MESH_HH


#include "../shader/Shader.hpp"
#include <vector>
#include "../include/glm/vec3.hpp"
#include "../include/glm/vec2.hpp"
#include "../geometry/Vertex.h"

enum FileFormat {jpg = GL_RGB, png = GL_RGBA};

class Mesh {

private:
    GLuint VAO, VBO, EBO;
    std::vector<Vertex> vertices;
    std::vector<GLuint> indices;
    glm::vec3 color;
    glm::vec2 position;

public:
    Mesh();
    Mesh(std::vector<Vertex> vertices, std::vector<GLuint> indices, glm::vec3 color);
    ~Mesh();
    void init();
    void draw(Shader shader) const;
    void setColor(glm::ivec3 color);
    void changePosition(glm::vec2 position);
    void loadTexture(const char* texturePath, GLuint& texture, FileFormat format);
};

#endif