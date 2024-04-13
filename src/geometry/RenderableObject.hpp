#ifndef RENDERABLEOBJECT_HH
#define RENDERABLEOBJECT_HH

#include <vector>
#include "../geometry/Vertex.h"
#include "../shader/Shader.hpp"
#include "../utils/Transformation.hpp"

#include <GL/glew.h>
#include <GLFW/glfw3.h>

class RenderableObject {

private:
    GLuint VAO, PVBO, CVBO, EBO;
    std::vector<Vertex> vertices;
    std::vector<GLuint> indices;
    glm::vec3 color;
    void init();
public:
    RenderableObject();
    RenderableObject(std::vector<Vertex> vertices);
    RenderableObject(std::vector<Vertex> vertices, glm::ivec3 color);
    RenderableObject(std::vector<Vertex> vertices, std::vector<GLuint> indices);
    RenderableObject(std::vector<Vertex> vertices, std::vector<GLuint> indices, glm::ivec3 color);
    virtual ~RenderableObject();
    virtual void draw(Shader shader) const;
    void setColor(glm::ivec3 color);
    void setPosition(GLfloat* transformMatrix, GLuint shaderID) const;

    const std::size_t getIndicesSize() const;
    const std::size_t getVerticiesSize() const;

    void setVertices(std::vector<Vertex> vertices);
    void setVertex(Vertex vertex);
}; 

#endif