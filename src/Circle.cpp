#include "geometry/Circle.hpp"

Circle::Circle(std::vector<Vertex> vertices) : RenderableObject {vertices} {

}

Circle::~Circle() {

}

void Circle::draw(Shader shader) const {
    RenderableObject::draw(shader);
    glDrawArrays(GL_TRIANGLE_FAN, 0, getVerticiesSize());
}