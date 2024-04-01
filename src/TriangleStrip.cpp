#include "geometry/TriangleStrip.hpp"

TriangleStrip::TriangleStrip() {
    init();
}

TriangleStrip::TriangleStrip(std::vector<glm::vec3> vertices, std::vector<glm::vec3> color, std::vector<GLuint> indices) {
    this->vertices = vertices;
    this->color = color;
    this->indices = indices;
    init();
}

void TriangleStrip::init() {
    //VAO
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);

    //VBO for Position
    glGenBuffers(1, &PVBO);
    glBindBuffer(GL_ARRAY_BUFFER, PVBO);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(glm::vec3), &(vertices[0]), GL_STATIC_DRAW);

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(
        0,                      // location attribute number in vertex shader  
        3,                      // size of the vertex attribute
        GL_FLOAT,               // type of the data
        GL_FALSE,               // if we want the data to be normalized
        sizeof(glm::vec3),      // stride and tells us the space between consecutive vertex attributes
        (void*)0                // offset of where the position data begins in the buffer
    );

    //VBO for Color
    glGenBuffers(1, &CVBO);
    glBindBuffer(GL_ARRAY_BUFFER, CVBO);
    glBufferData(GL_ARRAY_BUFFER, color.size() * sizeof(glm::vec3), &(color[0]), GL_STATIC_DRAW);

    glEnableVertexAttribArray(1);
    glVertexAttribPointer(
        1,                      // location attribute number in vertex shader  
        3,                      // size of the vertex attribute
        GL_FLOAT,               // type of the data
        GL_FALSE,               // if we want the data to be normalized
        sizeof(glm::vec3),      // stride and tells us the space between consecutive vertex attributes
        (void*)0                // offset of where the position data begins in the buffer
    );

    //EBO
    glGenBuffers(1, &EBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(GLuint), &(indices.at(0)), GL_STATIC_DRAW);
 
}

void TriangleStrip::draw(Shader shader) const {
    shader.use();
    glBindVertexArray(VAO);

    glDrawElements(GL_TRIANGLE_STRIP, indices.size(), GL_UNSIGNED_INT, 0);
}