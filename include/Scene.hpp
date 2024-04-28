#ifndef SCENE_HH
#define SCENE_HH

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <string>

#include "Camera.hpp"
#include "Shader.hpp"
#include "RenderableObject.hpp"
#include "ModelLoader.hpp"
#include "Mesh.hpp"

class Scene {
private:
    GLFWwindow* window;
    std::string programmName;
    GLuint height;
    GLuint width;

    std::vector<RenderableObject*> renderableObjects;
    Camera* camera;
    Shader shader;

    int initWindow() {
        // set version and inizialize glfw
        glfwInit();
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

        // create window 
        window = glfwCreateWindow(this->width, this->height, this->programmName.c_str(), NULL, NULL);
        if (!window) {
            std::cerr << "Failed to create Window" << std::endl;
            glfwTerminate();
            return -1;
        }
        return 0;
    }

public:
    Scene();
    Scene(GLuint width, GLuint height, std::string programmName);
    ~Scene();

    void addRenderableObject(RenderableObject* object);
    void setShader();

    // different window settings
    void cullFace(bool b);
    void polygonModeRasterized(bool b);
    void depthTest(bool b);

    void render();

    void draw();
    void processInput(GLFWwindow *window);

    GLFWwindow* getWindow() const;
};

#endif