#include "geometry/CircleHole.hpp"

CircleHole::CircleHole(std::vector<Vertex> vertices) : RenderableObject {vertices} {

}

CircleHole::~CircleHole() {

}

void CircleHole::draw(Shader shader) const {
    RenderableObject::draw(shader);
    glDrawArrays(GL_TRIANGLE_STRIP, 0, getVerticiesSize());
}