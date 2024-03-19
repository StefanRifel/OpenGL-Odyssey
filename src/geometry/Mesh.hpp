#ifndef MESH_HH
#define MESH_HH


#include "../shader/Shader.hpp"
#include <vector>
#include "../include/glm/vec3.hpp"

enum FileFormat {jpg = GL_RGB, png = GL_RGBA};

class Mesh {

private:
    GLuint VAO, VBO, EBO;
    std::vector<glm::vec3> vertices;
    std::vector<GLuint> indices;

public:
    Mesh();
    Mesh(std::vector<glm::vec3> vertices, std::vector<GLuint> indices);
    ~Mesh();
    void init();
    void draw(Shader shader) const;
    void loadTexture(const char* texturePath, GLuint& texture, FileFormat format);
};

#endif