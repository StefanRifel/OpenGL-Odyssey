#ifndef RenderSystem_HH
#define RenderSystem_HH

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <string>

#include "WindowManager.hpp"
#include "Camera.hpp"
#include "Shader.hpp"
#include "ModelLoader.hpp"

#include "../src/ecs/core/types/System.hpp"
#include "../src/ecs/core/types/Event.hpp"

#include "../src/ecs/core/Coordinator.hpp"


class RenderSystem : public ecs::System { 
public:
    WindowManager* windowManager;

    Camera camera;
    Shader shader;

public:
    RenderSystem();
    ~RenderSystem();

    bool init(WindowManager* windowManager);

    void createObject(const char* path);

    // different windowManager settings
    void cullFace(bool b);
    void polygonModeRasterized(bool b);
    void depthTest(bool b);

    void onChangeColor(Event e);

    void render();
    void processInput();
};

#endif