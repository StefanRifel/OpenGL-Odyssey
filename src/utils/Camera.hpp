#ifndef CAMERA_HH
#define CAMERA_HH

#include "vec3.hpp"
#include "mat4.hpp"
#include "Transformation.hpp"
#include <GLFW/glfw3.h>

#include "../include/glm/glm.hpp"
#include "../include/glm/gtc/matrix_transform.hpp"
#include "../include/glm/gtc/type_ptr.hpp"

#include "../shader/Shader.hpp"

class Camera {

private:
    
public:
    glm::vec3 cameraPos;
    glm::vec3 cameraFront;
    glm::vec3 cameraUp;

    Camera();
    ~Camera();
    void look(Shader& shader);
};

#endif