#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include <cmath>

#include "shader/Shader.hpp"
#include "utils/Camera.hpp"
#include "utils/vec3.hpp"
#include "utils/Transformation.hpp"
#include "utils/ModelLoader.hpp"

#include "geometry/Mesh.hpp"

Shader shader;

Camera* camera = new Camera {};

std::vector<RenderableObject*> renderableObjects;

void init(void) {
    shader.createShader("../shaders/shader.vs", "../shaders/shader.fs");

    vec3 color {255, 112, 112};

    
    

    ModelLoader loader {};
    const char* path = "../assets/models/human.obj";
    std::vector<Vertex> inVertices;
    std::vector<GLuint> inFaces;
    loader.load(path, inVertices, inFaces);

    Mesh* teapot  = new Mesh {inVertices, inFaces};
    renderableObjects.push_back(teapot);


    path = "../assets/models/cube.obj";
    inVertices.clear();
    inFaces.clear();
    loader.load(path, inVertices, inFaces);

    for (size_t i = 0; i < 3; i++) {
        Mesh* cube = new Mesh {inVertices, inFaces};
        renderableObjects.push_back(cube);
    }
}

void draw(void) {
    glClearColor(0.94f, 0.93f, 0.81f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
    camera->look(shader);
    for (RenderableObject* obj : renderableObjects) {
        Transformation::lookAt(camera->cameraPos, camera->cameraFront, camera->cameraUp);
        obj->draw(shader);
    }
}

void processInput(GLFWwindow *window) {

    if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
    glfwSetWindowShouldClose(window, true);


    const float cameraSpeed = 0.05f; // adjust accordingly

    // Zoom camera out = "." and in = ","
    if (glfwGetKey(window, GLFW_KEY_COMMA) == GLFW_PRESS) {
        camera->cameraPos.z() -= cameraSpeed;
        camera->radiusXZ = camera->cameraPos.z();
        std::cout << "zoom in: " << camera->cameraPos << std::endl;
    } else if (glfwGetKey(window, GLFW_KEY_PERIOD) == GLFW_PRESS) {
        camera->cameraPos.z() += cameraSpeed;
        camera->radiusXZ = camera->cameraPos.z();
        std::cout << "zoom out: " << camera->cameraPos << std::endl;
    }

    // change position and point of view of the camera
    if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS) {
        camera->cameraPos.y() += cameraSpeed;
        camera->cameraFront.y() += cameraSpeed;
        std::cout << "move camera up: " << camera->cameraPos << std::endl;
    } else if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS) {
        camera->cameraPos.y() -= cameraSpeed;
        camera->cameraFront.y() -= cameraSpeed;
        std::cout << "move camera down: " << camera->cameraPos << std::endl;
    } else if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS) {
        camera->cameraPos.x() -= cameraSpeed;
        camera->cameraFront.x() -= cameraSpeed;
        std::cout << "move camera left: " << camera->cameraPos << std::endl;
    } else if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS) {
        camera->cameraPos.x() += cameraSpeed;
        camera->cameraFront.x() += cameraSpeed;
        std::cout << "move camera right: " << camera->cameraPos << std::endl;
    }

    // rotate model around in x and y axis
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
        camera->anlgeXZ--;
        vec3 newPos = Transformation::calcPointOnCircle(camera->anlgeXZ, camera->radiusXZ);
        camera->cameraPos.x() = newPos.x();
        camera->cameraPos.z() = newPos.y();
        std::cout << "turn camera around left: " << camera->cameraPos << std::endl;
    }
    

    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
        camera->anlgeXZ++;
        vec3 newPos = Transformation::calcPointOnCircle(camera->anlgeXZ, camera->radiusXZ);
        camera->cameraPos.x() = newPos.x();
        camera->cameraPos.z() = newPos.y();
        std::cout << "turn camera around right: " << camera->cameraPos << std::endl;
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

    glEnable(GL_CULL_FACE);
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