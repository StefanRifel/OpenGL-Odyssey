#include "geometry/RectangleShaderExperiment.hpp"

RectangleShaderExperiment::RectangleShaderExperiment() {
    init();
}

RectangleShaderExperiment::RectangleShaderExperiment(std::vector<glm::vec3> verticies, std::vector<GLfloat> vertValue, std::vector<GLuint> indices) {
    this->vertices = verticies;
    this->vertValue = vertValue;
    this->indices = indices;
    init();
}

void RectangleShaderExperiment::init() {
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
    glGenBuffers(1, &VVBO);
    glBindBuffer(GL_ARRAY_BUFFER, VVBO);
    glBufferData(GL_ARRAY_BUFFER, vertValue.size() * sizeof(GLfloat), &(vertValue[0]), GL_STATIC_DRAW);

    glEnableVertexAttribArray(1);
    glVertexAttribPointer(
        1,                      // location attribute number in vertex shader  
        1,                      // size of the vertex attribute
        GL_FLOAT,               // type of the data
        GL_FALSE,               // if we want the data to be normalized
        sizeof(GLfloat),        // stride and tells us the space between consecutive vertex attributes
        (void*)0                // offset of where the position data begins in the buffer
    );

    //EBO
    glGenBuffers(1, &EBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(GLuint), &(indices.at(0)), GL_STATIC_DRAW);
}

void RectangleShaderExperiment::draw(Shader shader) const {
    shader.use();
    glBindVertexArray(VAO);

    // Set green and red color to uniform variable in fragment shader 
    float vertexFragColor1 = glGetUniformLocation(shader.ID, "fragColor1");
    glUniform3f(vertexFragColor1, 0.0f, 1.0f, 0.0f);

    float vertexFragColor2 = glGetUniformLocation(shader.ID, "fragColor2");
    glUniform3f(vertexFragColor2, 1.0f, 0.0f, 0.0f);

    glDrawElements(GL_TRIANGLE_STRIP, indices.size(), GL_UNSIGNED_INT, 0);
}