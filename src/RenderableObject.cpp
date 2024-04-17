#include "geometry/RenderableObject.hpp"

RenderableObject::RenderableObject() : color {0.04f, 0.38f, 0.69f} {
    init();
}

RenderableObject::RenderableObject(std::vector<Vertex> vertices) : color {0.04f, 0.38f, 0.69f}, vertices {vertices} {
    init();
}

RenderableObject::RenderableObject(std::vector<Vertex> vertices, glm::ivec3 color) : color {0.04f, 0.38f, 0.69f}, vertices {vertices} {
    setColor(color);
    init();
}

RenderableObject::RenderableObject(std::vector<Vertex> vertices, std::vector<GLuint> indices) : color {0.04f, 0.38f, 0.69f}, vertices {vertices}, indices {indices} {
    init();
}

RenderableObject::RenderableObject(std::vector<Vertex> vertices, std::vector<GLuint> indices, glm::ivec3 color) : color {color}, vertices {vertices}, indices {indices} {
    init();
}

RenderableObject::~RenderableObject() {

}

void RenderableObject::init() {
    // VAO
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);

    // VBO for Position
    glGenBuffers(1, &PVBO);
    glBindBuffer(GL_ARRAY_BUFFER, PVBO);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), &(vertices[0]), GL_STATIC_DRAW);

    glVertexAttribPointer(
        0,                      // location attribute number in vertex shader  
        3,                      // size of the vertex attribute
        GL_FLOAT,               // type of the data
        GL_FALSE,               // if we want the data to be normalized
        sizeof(Vertex),         // stride and tells us the space between consecutive vertex attributes
        (void*)0                // offset of where the position data begins in the buffer
    );
    glEnableVertexAttribArray(0);

    // VBO for Color
    glGenBuffers(1, &CVBO);
    glBindBuffer(GL_ARRAY_BUFFER, CVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(color), &color, GL_STATIC_DRAW);

    glVertexAttribPointer(
        1,                      
        3,                    
        GL_FLOAT,              
        GL_FALSE,            
        sizeof(color),        
        (void*)0  
    );
    glEnableVertexAttribArray(1);

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

    float vertexFragColor = glGetUniformLocation(shader.ID, "fragColor");
    glUniform3f(vertexFragColor, color.r, color.g, color.b);
/*
    std::cout << "--------Start--------" << std::endl;
    std::cout << "--------Scale--------" << std::endl;
*/
    GLfloat in[16];
    Transformation::identity(in);

    GLfloat rotateResultx[16] = {0.0f};
    Transformation::rotateX(rotateResultx, in, 75);
    //Transformation::printM4x4(rotateResultx, "first rotation z result");

    GLfloat rotateResulty[16] = {0.0f};
    Transformation::rotateY(rotateResulty, rotateResultx, 25);
    //Transformation::printM4x4(rotateResult1, "first rotation z result");

    GLfloat scaleResult1[16] = {0.0f};
    GLfloat scaleV1[3] = {
        0.5f, 0.5f, 0.5f // x, y, z
    };

    Transformation::scale(scaleResult1, rotateResulty, scaleV1);
    /*
    Transformation::printM4x4(scaleResult1, "first scale result");

    GLfloat scaleResult2[16] = {0.0f};
    GLfloat scaleV2[3] = {
        0.8f, 0.3f, 1.0f
    };
    Transformation::scale(scaleResult2, scaleResult1, scaleV2);
    Transformation::printM4x4(scaleResult2, "secound scale result");

    std::cout << "--------RotateZ--------" << std::endl;
    
    GLfloat rotateResult1[16] = {0.0f};
    Transformation::rotateZ(rotateResult1, scaleResult2, 30);
    Transformation::printM4x4(rotateResult1, "first rotation z result");
    
    std::cout << "--------Translate--------" << std::endl;
    
    GLfloat translateResult1[16] = {0.0f};
    GLfloat translateV1[3] = {
        0.3f, 0.2f, 0.0f // x, y, z
    };
    Transformation::translate(translateResult1, rotateResult1, translateV1);
    Transformation::printM4x4(translateResult1, "first translation result");

    GLfloat translateResult2[16] = {0.0f};
    GLfloat translateV2[3] = {
        0.1f, 0.3f, 0.0f
    };
    Transformation::translate(translateResult2, translateResult1, translateV2);
    Transformation::printM4x4(translateResult2, "first translation result");

    std::cout << "--------End--------" << std::endl;

    //Transformation::rotateZ(out, in, 60);
    */
    float vertexTransform = glGetUniformLocation(shader.ID, "transform");
    glUniformMatrix4fv(vertexTransform, 1, GL_FALSE, scaleResult1);
    
    glEnable(GL_CULL_FACE);
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

void RenderableObject::setPosition(GLfloat* transformMatrix, GLuint shaderID) const {
    float vertexTransform = glGetUniformLocation(shaderID, "transform");
    glUniformMatrix4fv(vertexTransform, 1, GL_FALSE, transformMatrix);
}

const std::vector<Vertex>& RenderableObject::getVertices() const {
    return vertices;
}

const std::vector<GLuint>& RenderableObject::getIndices() const {
    return indices;
}