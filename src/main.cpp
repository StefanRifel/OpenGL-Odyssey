#include "../include/Window.hpp"
//#include "../include/Scene.hpp"

int main(void) {
    std::cout << "Welcome to OpenGL Odyssey!" << std::endl;

    Window* window = new Window {1024, 768, "OpenGL-Odyssey"};
    window->init();
    window->render();
    delete(window);
    
    
    /*
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
    */
    return 0;
}