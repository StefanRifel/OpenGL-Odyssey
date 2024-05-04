#ifndef SCENE_HH
#define SCENE_HH

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "../libs/ImGui/imgui.h"
#include "../libs/ImGui/imgui_impl_glfw.h"
#include "../libs/ImGui/imgui_impl_opengl3.h"

#include <string>

#include "Camera.hpp"
#include "Shader.hpp"
#include "RenderableObject.hpp"
#include "ModelLoader.hpp"
#include "Mesh.hpp"

class Scene {
public:
    std::vector<RenderableObject*> renderableObjects;
    Camera* camera;
    Shader shader;

public:
    Scene();
    ~Scene();

    void addRenderableObject(RenderableObject* object);
    void setShader();

    // different window settings
    void cullFace(bool b);
    void polygonModeRasterized(bool b);
    void depthTest(bool b);

    

    void draw();
    void processInput(GLFWwindow *window);

    GLFWwindow* getWindow() const;
};

#endif