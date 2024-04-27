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

    mat4 model {1.0f};
    
    vec3 s {0.3f, 0.3f, 0.3f};
    model = Transformation::scale(model, s);
    static int count = 0;
    if(count % 2 == 0) {
        vec3 t {5.0f, 1.0f, 0.0f};
        model = Transformation::translate(model, t);
        vec3 otherColor {77, 53, 147};
    } else {
        vec3 t {-3.0f, -2.0f, 0.0f};
        model = Transformation::translate(model, t);
    }
    count++;
    
    shader.setModel(model);

    //glEnable(GL_PRIMITIVE_RESTART);
    //glPrimitiveRestartIndex(0xFFFF);
    glDrawElements(GL_TRIANGLES, getIndicesSize(), GL_UNSIGNED_INT, 0);
}