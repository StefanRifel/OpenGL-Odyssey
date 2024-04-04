#include "geometry/Triangle.hpp"

Triangle::Triangle() {
}

Triangle::Triangle(std::vector<Vertex> vertices) : RenderableObject {vertices} {

}

Triangle::Triangle(std::vector<Vertex> vertices, glm::ivec3 color) : RenderableObject {vertices, color} {

}

Triangle::~Triangle() {

}

void Triangle::draw(Shader shader) const {
    RenderableObject::draw(shader);
    glDrawArrays(GL_TRIANGLES, 0, 3);
}