#include <stdio.h>
#include <iostream>
#include "utils/Logger.hpp"
#include "shader/Shader.hpp"

#define STB_IMAGE_IMPLEMENTATION
#include "include/stb_image.h"
#include "include/glm/vec3.hpp"

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <cmath>

enum FileFormat {jpg = GL_RGB, png = GL_RGBA};

Shader shaderProgram;
Shader shaderProgram2;
Shader shaderProgram3;
GLuint VAO;
GLuint VAO2;
GLuint VAO3;
GLuint texture1;
GLuint texture2;

void loadTexture(const char* texturePath, GLuint& texture, FileFormat format) {
    
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

void init(void) {
    shaderProgram.createShader("../shaders/shader.vs", "../shaders/shader.fs");
    shaderProgram2.createShader("../shaders/shader.vs", "../shaders/shader2.fs");
    shaderProgram3.createShader("../shaders/shader.vs", "../shaders/shader3.fs");

    // create triangle buffer
    GLfloat vertices[] = {
        0.5f, 0.5f, 0.0f, 1.0f, 0.0f, 0.0f,// top right
        0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f, // bottom right
        //-0.5f, -0.5f, 0.0f, // bottom left
        -0.5f, 0.5f, 0.0f, 0.0f, 0.0f, 1.0f// top left
    };

    GLuint indices[] = { // note that we start from 0!
        0, 1, 3, // first triangle
        1, 2, 3, // second triangle
    };


    GLfloat rectangleVertices [] = {
        // position       , colors          , texture coordinates
        //  X,     Y,    Z,    R,    G,    B,    S,    T
        -1.0f, -1.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, //left-bottom
        -1.0f,  0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, //left-top
         0.0f,  0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 1.0f, 1.0f, //right-top
         0.0f, -1.0f, 0.0f, 1.0f, 1.0f, 0.0f, 1.0f, 0.0f, //right-bottom
    };

    GLfloat trigVertices[] = {
        -1.0f, 1.0f, 0.0f,
        1.0f, 1.0f, 0.0f,
        0.0f, 0.6f, 0.0f
    };

    GLfloat textureCordinates[] = {
        0.0f, 0.0f,
        2.0f, 0.0f,
        0.5f, 1.0f
    };

    //VBO
    GLuint VBO;
    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    //VBO2
    GLuint VBO2;
    glGenBuffers(1, &VBO2);
    glBindBuffer(GL_ARRAY_BUFFER, VBO2);
    glBufferData(GL_ARRAY_BUFFER, sizeof(trigVertices), trigVertices, GL_STATIC_DRAW);
    //VBO3
    GLuint VBO3;
    glGenBuffers(1, &VBO3);
    glBindBuffer(GL_ARRAY_BUFFER, VBO3);
    glBufferData(GL_ARRAY_BUFFER, sizeof(rectangleVertices), rectangleVertices, GL_STATIC_DRAW);

    //VAO
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glVertexAttribPointer(
        0, 
        3, 
        GL_FLOAT, 
        GL_FALSE, 
        6 * sizeof(GL_FLOAT),
        (void*)0
    );
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(
        1, 
        3, 
        GL_FLOAT, 
        GL_FALSE, 
        6 * sizeof(GL_FLOAT),
        (void*)(3 * sizeof(GL_FLOAT))
    );
    glEnableVertexAttribArray(1);
    //VAO2
    glGenVertexArrays(1, &VAO2);
    glBindVertexArray(VAO2);
    glBindBuffer(GL_ARRAY_BUFFER, VBO2);
    glVertexAttribPointer(
        0, 
        3, 
        GL_FLOAT, 
        GL_FALSE, 
        3 * sizeof(float),
        (void*)0
    );
    glEnableVertexAttribArray(0);
    //VAO3
    glGenVertexArrays(1, &VAO3);
    glBindVertexArray(VAO3);
    glBindBuffer(GL_ARRAY_BUFFER, VBO3);
    glVertexAttribPointer(
        0,                  // location attribute number in vertex shader             
        3,                  // size of the vertex attribute
        GL_FLOAT,           // type of the data
        GL_FALSE,           // if we want the data to be normalized
        8 * sizeof(float),  // stride and tells us the space between consecutive vertex attributes
        (void*)0            // offset of where the position data begins in the buffer
    );
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(
        1, 
        3, 
        GL_FLOAT, 
        GL_FALSE, 
        8 * sizeof(float),
        (void*)(sizeof(float) * 3)
    );
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(
        2, 
        2, 
        GL_FLOAT, 
        GL_FALSE, 
        8 * sizeof(float),
        (void*)(sizeof(float) * 6)
    );
    glEnableVertexAttribArray(2);

    loadTexture("../assets/wall.jpg", texture1, jpg);
    loadTexture("../assets/awesomeface.png", texture2, png);

    //EBO
    GLuint EBO;
    glGenBuffers(1, &EBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
}

void draw(void) {
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    // draw first triangle
    shaderProgram.use();
    glBindVertexArray(VAO);
    glDrawArrays(GL_TRIANGLES, 0, 3);

    // draw secound triangle
    shaderProgram2.use();
    
    float timeValue = glfwGetTime();
    float greenValue = (sin(timeValue) / 2.0f) + 0.5f;
    int vertexColorLocation = glGetUniformLocation(shaderProgram2.ID, "ourColor");
    if(vertexColorLocation) {
        Logger::logerr("failed to load ourColor from fragment shader: ");
        std::cout << vertexColorLocation << std::endl;
    }  
    glUniform4f(vertexColorLocation, 0.0f, greenValue, 0.0f, 1.0f);

    // render step
    glBindVertexArray(VAO2);
    glDrawArrays(GL_TRIANGLES, 0 , 3);

    // rectangle
    shaderProgram3.use();
    shaderProgram3.setInt("texture1", 0);
    shaderProgram3.setInt("texture2", 1); 
    
    glActiveTexture(GL_TEXTURE0); // activate texture unit first
    glBindTexture(GL_TEXTURE_2D, texture1);
    glActiveTexture(GL_TEXTURE1); // activate texture unit first
    glBindTexture(GL_TEXTURE_2D, texture2);
    glBindVertexArray(VAO3);

    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
    
}

void processInput(GLFWwindow *window) {
    if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
    glfwSetWindowShouldClose(window, true);
}

void framebuffer_size_callback(GLFWwindow *window, int width, int height) {
    glViewport(0,0, width, height);
}

int main(void) {
    Logger::log("Welcome to OpenGL Odyssey!");

    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    
    GLFWwindow *window = glfwCreateWindow(1024, 768, "OpenGL Odyssey", NULL, NULL);
    if (!window)
    {
        Logger::logerr("Failed to create Window");
        glfwTerminate();
        return -1;
    }

    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    glfwMakeContextCurrent(window);
    glewInit();

    init();

    // set line or fill from graphic
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

    int nrAttributes;
    glGetIntegerv(GL_MAX_VERTEX_ATTRIBS, &nrAttributes);
    std::cout << "Maximum nr of vertex attributes supported: " << nrAttributes << std::endl;

    // render loop
    while (!glfwWindowShouldClose(window))
    {
        // input
        processInput(window);

        // rendering commands here
        draw();

        // check and call events and swap the buffers
        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    
    glfwTerminate();

    return 0;
}