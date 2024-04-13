#include <iostream>

#include "shader/Shader.hpp"
#include "utils/ModelLoader.hpp"
#include "utils/Transformation.hpp"

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "geometry/Triangle.hpp"
#include "geometry/Rectangle.hpp"
#include "geometry/Circle.hpp"
#include "geometry/CircleHole.hpp"
#include "geometry/Mesh.hpp"

#include <cmath>

Shader shader;

std::vector<RenderableObject*> renderableObjects;

std::vector<Vertex> calcCircleVertices(Vertex origin, GLfloat radius) {
    std::vector<Vertex> circleVertices;
    circleVertices.push_back(origin);
    for(float angle = 360; angle >= 0; angle--) {
        float x = (float)(radius * cos(angle * M_PI /180));
        x += origin.position.x;
        float y = (float)(radius * sin(angle * M_PI /180));
        y += origin.position.y;
        circleVertices.push_back(Vertex {glm::vec3 {x, y, 0.0f}});
    }
    return circleVertices;
}

std::vector<Vertex> calcCircleHoleVertices(Vertex origin, GLfloat innerRadius, GLfloat outerRadius) {
    std::vector<Vertex> circleVertices;
    for(float angle = 360; angle >= 0; angle --) {
        float x = (float)(outerRadius * cos(angle * M_PI /180));
        x += origin.position.x;
        float y = (float)(outerRadius * sin(angle * M_PI /180));
        y += origin.position.y;
        circleVertices.push_back(Vertex {glm::vec3 {x, y, 0.0f}});

        x = (float)(innerRadius * cos(angle * M_PI /180));
        x += origin.position.x;
        y = (float)(innerRadius * sin(angle * M_PI /180));
        y += origin.position.y;
        circleVertices.push_back(Vertex {glm::vec3 {x, y, 0.0f}});
    }
    return circleVertices;
}

void init(void) {
    shader.createShader("../shaders/shader.vs", "../shaders/shader.fs");


    glm::ivec3 color {255, 112, 112};
    glm::ivec3 differentColor {57, 36, 103};

    std::vector<Vertex> verticesTriangle = {
        Vertex {glm::vec3 {0.0f, 0.5f, 0.0f}},
        Vertex {glm::vec3 {-0.5f, -0.5f, 0.0f}},
        Vertex {glm::vec3 {0.5f, -0.5f, 0.0f}}
    };

    std::vector<Vertex> verticesRectangle = {
        Vertex {glm::vec3 {-1.0f, 1.0f, 0.0f}},
        Vertex {glm::vec3 {-1.0f, 0.8f, 0.0f}},
        Vertex {glm::vec3 {-0.5f, 1.0f, 0.0f}},
        Vertex {glm::vec3 {-0.5f, 0.8f, 0.0f}},
        
    };

    std::vector<GLuint> indicesRectangle = {
        0, 1, 2,
        3, 2, 1
    };

    std::vector<Vertex> verticesCircle {calcCircleVertices(Vertex {glm::vec3 {0.5f, 0.5f, 0.0f}}, 0.8f)};

    std::vector<Vertex> verticesCircleHole = calcCircleHoleVertices(Vertex {glm::vec3 {-0.5f, 0.5f, 0.0f}}, 0.1f, 0.5f);

    ModelLoader loader {"../assets/models/hsh_logo.txt"};
    loader.load();

    Triangle* triangle = new Triangle {verticesTriangle, color};

    triangle->setColor(differentColor);

    Rectangle* rectangle = new Rectangle {verticesRectangle, indicesRectangle};

    rectangle->setColor(color);

    Circle* circle = new Circle {verticesCircle};

    CircleHole* circleHole = new CircleHole{verticesCircleHole};
    circleHole->setColor(differentColor);

    Mesh* hsh = new Mesh {loader.getVertices(), loader.getFaces()};
    hsh->setColor(color);

    //renderableObjects.push_back(triangle);
    //renderableObjects.push_back(rectangle);
    //renderableObjects.push_back(circle);
    //renderableObjects.push_back(circleHole);
    renderableObjects.push_back(hsh);
}

void draw(void) {
    glClearColor(0.94f, 0.93f, 0.81f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    for (RenderableObject* obj : renderableObjects) {
        obj->draw(shader);
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