#include "geometry/Mesh.hpp"

Mesh::Mesh() {
    init();
}

Mesh::Mesh(std::vector<Vertex> vertices, std::vector<GLuint> indices, glm::vec3 color) {
    this->vertices = vertices;
    this->indices = indices;
    this->color = color;
    this->position = glm::vec2 {0.0, 0.0};

    init();
}

Mesh::~Mesh() {

}

void Mesh::init() {
    //VBO
    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), &(vertices[0]), GL_STATIC_DRAW);

    //VAO
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glVertexAttribPointer(
        0,                      // location attribute number in vertex shader  
        3,                      // size of the vertex attribute
        GL_FLOAT,               // type of the data
        GL_FALSE,               // if we want the data to be normalized
        sizeof(Vertex),   // stride and tells us the space between consecutive vertex attributes
        (void*)0                // offset of where the position data begins in the buffer
    );
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(
        1,                      // location attribute number in vertex shader  
        3,                      // size of the vertex attribute
        GL_FLOAT,               // type of the data
        GL_FALSE,               // if we want the data to be normalized
        sizeof(Vertex),   // stride and tells us the space between consecutive vertex attributes
        (void*)(sizeof(glm::vec3))               // offset of where the position data begins in the buffer
    );
    glEnableVertexAttribArray(1);

    //EBO
    glGenBuffers(1, &EBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(GLuint), &(indices.at(0)), GL_STATIC_DRAW);
}

void Mesh::draw(Shader shader) const {
    shader.use();
    glBindVertexArray(VAO);

    float vertexColorLocation = glGetUniformLocation(shader.ID, "color");
    glUniform3f(vertexColorLocation, this->color.x, this->color.y, this->color.z);

    float vertexPositionLocation = glGetUniformLocation(shader.ID, "position");
    glUniform2f(vertexPositionLocation, this->position.x, this->position.y);

    glm::mat4 trans = glm::mat4(1.0f);
    //trans = glm::translate(trans, glm::vec3(0.5f, -0.5f, 0.0f));
    trans = glm::rotate(trans, (float)glfwGetTime(), glm::vec3(0.0f, 0.0f, 1.0f));
    trans = glm::scale(trans, glm::vec3(0.5, 0.5, 0.5));

    unsigned int transformLoc = glGetUniformLocation(shader.ID,"transform");
    glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(trans));


    glm::mat4 model = glm::mat4(1.0f);
    model = glm::rotate(model, glm::radians(-55.0f), glm::vec3(1.0f, 0.0f, 0.0f));

    glm::mat4 view = glm::mat4(1.0f);
    // note that we’re translating the scene in the reverse direction
    view = glm::translate(view, glm::vec3(0.0f, 0.0f, -3.0f));

    glm::mat4 projection;
    projection = glm::perspective(glm::radians(45.0f), 800.0f / 600.0f, 0.1f, 100.0f);

    int modelLoc = glGetUniformLocation(shader.ID, "model");
    glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));

    int viewLoc = glGetUniformLocation(shader.ID, "view");
    glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));

    int projectionLoc = glGetUniformLocation(shader.ID, "projection");
    glUniformMatrix4fv(projectionLoc, 1, GL_FALSE, glm::value_ptr(projection));

    glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);
}

void Mesh::setColor(glm::ivec3 color) {
    this->color.x = ((100.0f / 255) * color.x) / 100;
    this->color.y = ((100.0f / 255) * color.y) / 100;
    this->color.z = ((100.0f / 255) * color.z) / 100;
}

void Mesh::changePosition(glm::vec2 position) {
    this->position.x = position.x;
    this->position.y = position.y; 
}