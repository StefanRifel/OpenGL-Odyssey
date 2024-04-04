#include "geometry/Mesh.hpp"
#include <iostream>

Mesh::Mesh() {

}

Mesh::Mesh(std::vector<Vertex> vertices) : RenderableObject {vertices} {

}

Mesh::Mesh(std::vector<Vertex> vertices, std::vector<GLuint> indices) : RenderableObject {vertices, indices} {

}

Mesh::~Mesh() {

}

void Mesh::draw(Shader shader) const {
    RenderableObject::draw(shader);

    glEnable(GL_PRIMITIVE_RESTART);
    glPrimitiveRestartIndex(0xFFFF);
    glDrawElements(GL_TRIANGLE_STRIP, getIndicesSize(), GL_UNSIGNED_INT, 0);
}