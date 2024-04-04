#include "geometry/Rectangle.hpp"

Rectangle::Rectangle() {
    
}

Rectangle::Rectangle(std::vector<Vertex> vertices, std::vector<GLuint> indices) : RenderableObject {vertices, indices} {

}

Rectangle::~Rectangle() {

}

void Rectangle::draw(Shader shader) const {
    RenderableObject::draw(shader);
    glDrawElements(GL_TRIANGLES, getIndicesSize(), GL_UNSIGNED_INT, 0);
}