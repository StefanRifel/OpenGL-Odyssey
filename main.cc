#include <stdio.h>
#include <iostream>
#include "Logger.hh"

#include <GL/glew.h>
#include <GLFW/glfw3.h>

GLuint program;
GLuint vao;

void init(void) {
    // create and compile vertex shader


    // create and comile fragment shader


    // create and link shader program
    

    // create triangle buffer


}

void draw(void) {
    
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
        printf("Failed to create Window\n");
        glfwTerminate();
        return -1;
    }

    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    glfwMakeContextCurrent(window);
    glewInit();

    init();
    
    while (!glfwWindowShouldClose(window))
    {
        draw();
        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    
    glfwTerminate();

    return 0;
}