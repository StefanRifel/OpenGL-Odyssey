#include <stdio.h>
#include <iostream>
#include "utils/Logger.hpp"
#include "utils/ModelLoader.hpp"
#include "shader/Shader.hpp"
#include "geometry/Triangle.hpp"
#include "geometry/Rectangle.hpp"
#include "geometry/Mesh.hpp"

#include "include/glm/vec3.hpp"

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <cmath>

//enum FileFormat {jpg = GL_RGB, png = GL_RGBA};

Shader shaderProgram;
Shader shaderProgram2;
Shader shaderProgram3;

//GLuint texture1;
//GLuint texture2;

std::vector<Mesh> objects;

void init(void) {
    shaderProgram.createShader("../shaders/shader.vs", "../shaders/shader.fs");
    shaderProgram2.createShader("../shaders/shader.vs", "../shaders/shader2.fs");
    shaderProgram3.createShader("../shaders/shader.vs", "../shaders/shader3.fs");

    //loadTexture("../assets/wall.jpg", texture1, jpg);
    //loadTexture("../assets/awesomeface.png", texture2, png);

    glm::vec3 a {-1.0f, 1.0f, 0.0f};
    glm::vec3 b {1.0f, 1.0f, 0.0};
    glm::vec3 c {0.0f, 0.6f, 0.0};
    
    glm::vec3 r1 {-1.0f, -1.0f, 0.0f};
    glm::vec3 r2 {-1.0f,  0.0f, 0.0f};
    glm::vec3 r3 {0.0f,  0.0f, 0.0f};
    glm::vec3 r4 {0.0f, -1.0f, 0.0f};
    
    Triangle triangle {a, b, c};

    Rectangle rectangle {r1, r2, r3, r4};

    ModelLoader loader {"../assets/models/hsh_logo.txt"};
    loader.load();

    Mesh mesh {loader.getVertices(), loader.getFaces()};
    objects.push_back(mesh);
}

void draw(void) {
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    for (Mesh mesh : objects) {
        mesh.draw(shaderProgram);
    }
    
    /*
    float timeValue = glfwGetTime();
    float greenValue = (sin(timeValue) / 2.0f) + 0.5f;
    int vertexColorLocation = glGetUniformLocation(shaderProgram2.ID, "ourColor");
    if(vertexColorLocation) {
        Logger::logerr("failed to load ourColor from fragment shader: ");
        std::cout << vertexColorLocation << std::endl;
    }  
    glUniform4f(vertexColorLocation, 0.0f, greenValue, 0.0f, 1.0f);
    */

    /*
    // rectangle
    shaderProgram3.use();
    shaderProgram3.setInt("texture1", 0);
    shaderProgram3.setInt("texture2", 1); 
    
    glActiveTexture(GL_TEXTURE0); // activate texture unit first
    glBindTexture(GL_TEXTURE_2D, texture1);
    glActiveTexture(GL_TEXTURE1); // activate texture unit first
    glBindTexture(GL_TEXTURE_2D, texture2);
    glBindVertexArray(VAO3);
    */
    
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
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

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