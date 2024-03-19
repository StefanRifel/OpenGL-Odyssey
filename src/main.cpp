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
#include <ctime>

Shader shaderProgram;

std::vector<Mesh> objects;
float winkel {0};

std::vector<unsigned int> generateRandomColorCode() {
    std::vector<unsigned int> colorCode;
    std::srand(std::time(nullptr));
    for(int i = 0; i < 3; i++) {
        colorCode.push_back(std::rand() % 255);
    }
    return colorCode;
}

glm::vec2 calcPointOnCircle(float radius) {
    glm::vec2 koordiante;
    if(winkel == 360) {
        winkel = 0;
    }
    koordiante.x = (float)(radius * cos(winkel * M_PI /180));
    koordiante.y = (float)(radius * sin(winkel * M_PI /180));
    winkel++;
    return koordiante;
}

void init(void) {
    shaderProgram.createShader("../shaders/shader.vs", "../shaders/shader.fs");

    glm::vec3 color {0.4f, 0.2f, 0.5f};

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

    Mesh mesh {loader.getVertices(), loader.getFaces(), color};
    //mesh.setColor(glm::ivec3 {220, 60, 5}); hochschule farbe
    objects.push_back(mesh);

    calcPointOnCircle(0.3);
}

void draw(void) {
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    for (Mesh mesh : objects) {
        std::vector<unsigned int> code = generateRandomColorCode();
        mesh.setColor(glm::ivec3 {code.at(0) , code.at(1), code.at(2)});
        glm::vec2 position = calcPointOnCircle(0.7f);
        mesh.changePosition(glm::vec2 {position.x, position.y});
        mesh.draw(shaderProgram);
    }
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