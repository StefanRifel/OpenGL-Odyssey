#include "utils/Camera.hpp"

Camera::Camera() {
    this->cameraPos = {3.0f, 3.0f, 3.0f};
    this->cameraFront = {0.0f, 0.0f, 0.0f};
    this->cameraUp = {0.0f, 1.0f, 0.0f};
}

Camera::~Camera() {

}

void Camera::look(Shader& shader) {

    // set view matrix in shader
    shader.setView(Transformation::lookAt(vec3(0.0f, 0.0f, 3.0f), vec3(0.0f, 0.0f, 0.0f), vec3(0.0f, 1.0f, 0.0f)));

    // set projection matrix in shader
    shader.setProjection(Transformation::perspective(45.0f, 800.0f / 600.0f, 0.1f, 100.0f));
}