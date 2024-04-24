#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include <cmath>

#include "shader/Shader.hpp"
#include "utils/Camera.hpp"
#include "utils/vec3.hpp"

#include "geometry/Mesh.hpp"

Shader shader;

Camera* camera = new Camera {};

std::vector<RenderableObject*> renderableObjects;

vec3 calcCircleVertices(GLfloat angle) {
    vec3 cameraPos {};
    
    float x = (float)(10.0f * cos(angle * M_PI /180));
    cameraPos.x() = x;
    float y = (float)(10.0f * sin(angle * M_PI /180));
    cameraPos.y() = y;
    
    return cameraPos;
}

void init(void) {
    shader.createShader("../shaders/shader.vs", "../shaders/shader.fs");

    vec3 color {255, 112, 112};

    std::vector<Vertex> vertices = {
        Vertex {vec3 {-1.0f, -1.0f, -1.0f}, vec3 {0.1f, 0.1, 0.1f}},
        Vertex {vec3(1, -1, -1) , vec3 {0.2f, 0.2, 0.2f}},
        Vertex {vec3(1, 1, -1), vec3 {0.3f, 0.3, 0.3f}},
        Vertex {vec3(-1, 1, -1), vec3 {0.4f, 0.4, 0.4f}},
        Vertex {vec3(-1, -1, 1), vec3 {0.5f, 0.5, 0.5f}},
        Vertex {vec3(1, -1, 1), vec3 {0.6f, 0.6, 0.6f}},
        Vertex {vec3(1, 1, 1), vec3 {0.7f, 0.7, 0.7f}},
        Vertex {vec3(-1, 1, 1), vec3 {0.8f, 0.8, 0.8f}}
    };

    std::vector<GLuint> indices = {
        0, 1, 3, 3, 1, 2,
        1, 5, 2, 2, 5, 6,
        5, 4, 6, 6, 4, 7,
        4, 0, 7, 7, 0, 3,
        3, 2, 7, 7, 2, 6,
        4, 5, 0, 0, 5, 1
    };

    for (size_t i = 0; i < 3; i++) {
        Mesh* cube = new Mesh {vertices, indices};
        renderableObjects.push_back(cube);
    }
}

void draw(void) {
    glClearColor(0.94f, 0.93f, 0.81f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    vec3 eye {0.0,0.0,3.0};
    vec3 lool {0.0,0.0,0.0};
    vec3 up {0.0,1.0,0.0};
    
    camera->look(shader);
    for (RenderableObject* obj : renderableObjects) {
        Transformation::lookAt(eye, lool, up);
        obj->draw(shader);
    }
}

void processInput(GLFWwindow *window) {

    if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
    glfwSetWindowShouldClose(window, true);

    const float cameraSpeed = 0.05f; // adjust accordingly
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
        std::cout << "W: " << camera->cameraPos << std::endl;
    }
    

    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
        std::cout << "S: " << camera->cameraPos << std::endl;
    }
    

    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
        std::cout << "A: " << camera->cameraPos << std::endl;
    }
    

    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
        std::cout << "D: " << camera->cameraPos << std::endl;
    }
}

void framebuffer_size_callback(GLFWwindow *window, int width, int height) {
    glViewport(0,0, width, height);
}

int main(void) {
    std::cout << "Welcome to OpenGL Odyssey!" << std::endl;

    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    
    GLFWwindow *window = glfwCreateWindow(1024, 768, "OpenGL Odyssey", NULL, NULL);
    if (!window) {
        std::cerr << "Failed to create Window" << std::endl;
        glfwTerminate();
        return -1;
    }

    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    glfwMakeContextCurrent(window);
    glewInit();

    init();

    // set line or fill from graphic
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    // enable depth test
    glEnable(GL_DEPTH_TEST);  

    int nrAttributes;
    glGetIntegerv(GL_MAX_VERTEX_ATTRIBS, &nrAttributes);
    std::cout << "Maximum nr of vertex attributes supported: " << nrAttributes << std::endl;

    // render loop
    while (!glfwWindowShouldClose(window))
    {
        // input
        processInput(window);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // rendering commands here
        draw();

        // check and call events and swap the buffers
        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    
    glfwTerminate();

    return 0;
}