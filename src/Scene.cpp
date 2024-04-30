#include "../include/Scene.hpp"

Scene::Scene() : width {1024}, height {768}, programmName {"no name given"} {
    initWindow();
    camera = new Camera {};
}

Scene::Scene(GLuint width, GLuint height, std::string programmName) : width {width}, height {height}, programmName {programmName} {
    initWindow();
    camera = new Camera {};
}

Scene::~Scene() {

}

void Scene::addRenderableObject(RenderableObject* object) {
    renderableObjects.push_back(object);
}

void Scene::setShader() {
    shader.createShader("../shaders/shader.vs", "../shaders/shader.fs");
}

void Scene::cullFace(bool b) {
    b ? glEnable(GL_CULL_FACE) : glDisable(GL_CULL_FACE);
}

void Scene::polygonModeRasterized(bool b) {
    b ? glPolygonMode(GL_FRONT_AND_BACK, GL_LINE) : glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
}

void Scene::depthTest(bool b) {
    b ? glEnable(GL_DEPTH_TEST) : glDisable(GL_DEPTH_TEST);
}

void Scene::render() {
    //imgui
    ImGui::CreateContext();
    ImGui::StyleColorsDark();
    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init();

    // render loop
    while (!glfwWindowShouldClose(window)) {
        //imgui
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();
        ImGui::Begin("Debug");
        float my_color[4];
        ImGui::ColorEdit4("Color", my_color);
        ImGui::End();

        // input
        processInput(window);
        
        // rendering commands here
        draw();

        //imgui
        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        // check and call events and swap the buffers
        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    //imgui
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();

    glfwTerminate();
}

void Scene::draw() {
    glClearColor(0.94f, 0.93f, 0.81f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
    camera->look(shader);
    for (RenderableObject* obj : renderableObjects) {
        Transformation::lookAt(camera->cameraPos, camera->cameraFront, camera->cameraUp);
        mat4 model {1.0f};
        shader.setModel(model);
        obj->draw(shader);
    }
}

void Scene::processInput(GLFWwindow* window) {
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

GLFWwindow* Scene::getWindow() const {
    return window;
}