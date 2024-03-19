#include "geometry/Rectangle.hpp"

Rectangle::Rectangle() {
    init();
}

Rectangle::Rectangle(glm::vec3 a, glm::vec3 b, glm::vec3 c, glm::vec3 d) {
    vertices.push_back(a);
    vertices.push_back(b);
    vertices.push_back(c);
    vertices.push_back(d);
    indices.push_back(0);
    indices.push_back(1);
    indices.push_back(3);
    indices.push_back(1);
    indices.push_back(2);
    indices.push_back(3);
    init();
}

Rectangle::~Rectangle() {

}

void Rectangle::init() {
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

    GLuint EBO;
    glGenBuffers(1, &EBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(GLuint), &(indices.at(0)), GL_STATIC_DRAW);
}

void Rectangle::draw(Shader shader) const {
    shader.use();
    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);
}