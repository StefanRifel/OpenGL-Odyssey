#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "../include/Mesh.hpp"
#include "../include/Scene.hpp"

void framebuffer_size_callback(GLFWwindow *window, int width, int height) {
    glViewport(0,0, width, height);
}

int main(void) {
    std::cout << "Welcome to OpenGL Odyssey!" << std::endl;

    Scene scene {1024, 768, "OpenGL-Odyssey"};
    // setup scene
    glfwSetFramebufferSizeCallback(scene.getWindow(), framebuffer_size_callback);
    glfwMakeContextCurrent(scene.getWindow());
    glewInit();
    scene.setShader();

    // create different objects
    ModelLoader loader {};
    const char* path = "../assets/models/sphere.obj";
    std::vector<Vertex> inVertices;
    std::vector<GLuint> inFaces;
    loader.load(path, inVertices, inFaces);

    Mesh* teapot  = new Mesh {inVertices, inFaces};
    vec3 color {255, 112, 112};
    teapot->setColor(color);
    scene.addRenderableObject(teapot);

    // scene settings
    scene.cullFace(true);
    scene.polygonModeRasterized(true);
    scene.depthTest(true);

    scene.render();

    return 0;
}