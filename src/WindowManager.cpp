#include "ecs/core/Coordinator.hpp"

#include "../include/WindowManager.hpp"

WindowManager::WindowManager(GLuint width, GLuint height, std::string programmName) 
: width {width}, height {height}, programmName {programmName}, 
window {nullptr}, isRunning {true} {
    openglContext = new OpenGLContext {};
    guiContext = new GUIContext {};
    uiPanel = new UIPanel {};
}

WindowManager::~WindowManager() {
    std::cout << "Good Bye!" << std::endl;
    glfwSetWindowShouldClose(window, true);
    delete(openglContext);
    delete(guiContext);
    delete(uiPanel);
}

void WindowManager::init() {
    // test implementaion ecs
    coordinator.init();
    coordinator.registerComponent<ecs::Renderable>();
    coordinator.registerComponent<ecs::Transform>();

    renderSystem = coordinator.registerSystem<RenderSystem>();
    ecs::Signature signature;
    signature.set(coordinator.getComponentType<ecs::Renderable>());
    signature.set(coordinator.getComponentType<ecs::Transform>());
    coordinator.setSystemSignature<RenderSystem>(signature);

    if(!openglContext->init(this)) {
        std::cerr << "ERROR::WINDOWMANAGER::FAILED_TO_INIT_OPENGLCONTEXT" << std::endl;
    }
    if(!guiContext->init(this)) {
        std::cerr << "ERROR::WINDOWMANAGER::FAILED_TO_INIT_GUICONTEXT" << std::endl;
    }
    if(!renderSystem->init(this)) {
        std::cerr << "ERROR::WINDOWMANAGER::FAILED_TO_INIT_RenderSystem" << std::endl;
    }

    // create example object
    const char* path = "../assets/models/earth.obj";
    renderSystem->createObject(path);
}

void WindowManager::render() {
    // render loop
    while (isRunning) {
        // (Your code calls glfwPollEvents())
        renderSystem->processInput();
        // ...
        // Start the Dear ImGui frame
        guiContext->preRender();
        uiPanel->render(coordinator);
        
        // Rendering
        // (Your code clears your framebuffer, renders your other stuff etc.)
        openglContext->preRender();
        
        renderSystem->render();
        
        guiContext->postRender();
        // (Your code calls glfwSwapBuffers() etc.)

        openglContext->postRender();
    }
}

void WindowManager::onResize(GLuint width, GLuint height) {
    this->width = width;
    this->height = height;
}

void WindowManager::onClose() {
    isRunning = false;
}