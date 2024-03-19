#include "geometry/Mesh.hpp"

#define STB_IMAGE_IMPLEMENTATION
#include "include/stb_image.h"

Mesh::Mesh() {
    init();
}

Mesh::Mesh(std::vector<Vertex> vertices, std::vector<GLuint> indices, glm::vec3 color) {
    this->vertices = vertices;
    this->indices = indices;
    this->color = color;

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

    glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);
}

void Mesh::setColor(glm::ivec3 color) {
    this->color.x = ((100.0f / 255) * color.x) / 100;
    this->color.y = ((100.0f / 255) * color.y) / 100;
    this->color.z = ((100.0f / 255) * color.z) / 100;
}

void Mesh::loadTexture(const char* texturePath, GLuint& texture, FileFormat format) {
    
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);
    // set the texture wrapping/filtering options (on currently bound texture)
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    // load and generate the texture
    int width, height, nrChannels;
    stbi_set_flip_vertically_on_load(true); // flip the y-axis during image loading
    unsigned char *data = stbi_load(texturePath, &width, &height, &nrChannels, 0);

    if (data) {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, format, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    } else {
        std::cout << "Failed to load texture" << std::endl;
    }

    stbi_image_free(data);
}