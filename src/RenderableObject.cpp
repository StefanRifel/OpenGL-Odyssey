#include "geometry/RenderableObject.hpp"

RenderableObject::RenderableObject() : color {0.0f, 0.0f, 1.0f} {
    init();
}

RenderableObject::RenderableObject(std::vector<Vertex> vertices) : color {0.0f, 0.0f, 1.0f}, vertices {vertices} {
    init();
}

RenderableObject::RenderableObject(std::vector<Vertex> vertices, std::vector<GLuint> indices) : color {0.0f, 0.0f, 1.0f}, vertices {vertices}, indices {indices} {
    init();
}

RenderableObject::~RenderableObject() {

}

void RenderableObject::init() {
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
        sizeof(Vertex),         // stride and tells us the space between consecutive vertex attributes
        (void*)0                // offset of where the position data begins in the buffer
    );
    glEnableVertexAttribArray(0);

    if(indices.size() != 0) {
        //EBO
        glGenBuffers(1, &EBO);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(GLuint), &(indices.at(0)), GL_STATIC_DRAW);
    }
}

void RenderableObject::draw(Shader shader) const {
    shader.use();
    glBindVertexArray(VAO);
}

void RenderableObject::setColor(glm::ivec3 color) {
    this->color.x = ((100.0f / 255) * color.x) / 100;
    this->color.y = ((100.0f / 255) * color.y) / 100;
    this->color.z = ((100.0f / 255) * color.z) / 100;
}

const std::size_t RenderableObject::getIndicesSize() const {
    return indices.size();
}

void RenderableObject::setVertices(std::vector<Vertex> vertices) {
    this->vertices = vertices;
}

const std::size_t RenderableObject::getVerticiesSize() const {
    return vertices.size();
}

void RenderableObject::setVertex(Vertex vertex) {
    this->vertices.push_back(vertex);
}