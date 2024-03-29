#ifndef MESH_HH
#define MESH_HH


#include "../shader/Shader.hpp"
#include <vector>
#include "../include/glm/vec3.hpp"
#include "../include/glm/vec2.hpp"
#include "../geometry/Vertex.h"

#include "../include/glm/glm.hpp"
#include "../include/glm/gtc/matrix_transform.hpp"
#include "../include/glm/gtc/type_ptr.hpp"

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
};

#endif