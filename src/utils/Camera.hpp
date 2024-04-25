#ifndef CAMERA_HH
#define CAMERA_HH

#include "vec3.hpp"
#include "mat4.hpp"
#include "Transformation.hpp"
#include <GLFW/glfw3.h>

#include "../shader/Shader.hpp"

class Camera {

private:
    
public:
    vec3 cameraPos;
    vec3 cameraFront;
    vec3 cameraUp;

    float radiusXZ;
    int anlgeXZ;

    Camera();
    ~Camera();
    void look(Shader& shader);
};

#endif