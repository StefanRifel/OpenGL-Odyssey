#include "../include/Scene.hpp"

Scene::Scene() {
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

void Scene::draw() {
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