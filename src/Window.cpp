#include "../include/Window.hpp"

Window::Window(GLuint width, GLuint height, std::string programmName) 
: width {width}, height {height}, programmName {programmName}, 
window {nullptr}, isRunning {true} {
    openglContext = new OpenGLContext {};
    guiContext = new GUIContext {};
}

Window::~Window() {
    std::cout << "Good Bye!" << std::endl;
    delete(openglContext);
    delete(guiContext);
}

void Window::init() {
    if(!openglContext->init(this)) {
        std::cout << "ERROR::WINDOW::FAILED_TO_INIT_OPENGLCONTEXT" << std::endl;
    }
    if(!guiContext->init(this)) {
        std::cout << "ERROR::WINDOW::FAILED_TO_INIT_GUICONTEXT" << std::endl;
    }
}

void Window::render() {
    // render loop
    while (isRunning) {
        // (Your code calls glfwPollEvents())
        // ...
        // Start the Dear ImGui frame
        guiContext->preRender();
        
        // Rendering
        // draw();
        // (Your code clears your framebuffer, renders your other stuff etc.)
        openglContext->preRender();
        
        guiContext->postRender();
        // (Your code calls glfwSwapBuffers() etc.)

        openglContext->postRender();
    }
}

void Window::onResize(GLuint width, GLuint height) {
    this->width = width;
    this->height = height;
}

void Window::onClose() {
    isRunning = false;
}