#include "../include/CameraControlSystem.hpp"

CameraControlSystem::CameraControlSystem() {
    //this->cameraPos = {0.0f, 0.0f, 3.0f};
    //this->cameraFront = {0.0f, 0.0f, 0.0f};
    //this->cameraUp = {0.0f, 1.0f, 0.0f};
}

void CameraControlSystem::look(Shader& shader, vec3 cameraPos, vec3 cameraFront, vec3 cameraUp) {

    // set view matrix in shader
    shader.setView(Transformation::lookAt(cameraPos, cameraFront, cameraUp));

    // set projection matrix in shader
    shader.setProjection(Transformation::perspective(45.0f, 800.0f / 600.0f, 0.1f, 100.0f));
}