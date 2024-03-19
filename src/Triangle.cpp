#include "geometry/Triangle.hpp"

Triangle::Triangle() {
    init();
}

Triangle::Triangle(glm::vec3 a, glm::vec3 b, glm::vec3 c) {
    vertices.push_back(a);
    vertices.push_back(b);
    vertices.push_back(c);
    init();
}

Triangle::~Triangle() {

}

void Triangle::init() {
    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(glm::vec3), &(vertices.at(0)), GL_STATIC_DRAW);

    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glVertexAttribPointer(
        0, 
        3, 
        GL_FLOAT, 
        GL_FALSE, 
        3 * sizeof(GL_FLOAT),
        (void*)0
    );
    glEnableVertexAttribArray(0);
}

void Triangle::draw(Shader shader) const {
    shader.use();
    glBindVertexArray(VAO);
    glDrawArrays(GL_TRIANGLES, 0, 3);
}