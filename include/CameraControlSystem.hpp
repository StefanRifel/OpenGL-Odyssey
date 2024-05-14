#ifndef CAMERACONTROLSYSTEM_HH
#define CAMERACONTROLSYSTEM_HH

#include "../libs/SMath/include/vec3.hpp"
#include "../libs/SMath/include/mat4.hpp"
#include "Transformation.hpp"

#include "Shader.hpp"

#include "../src/ecs/core/types/System.hpp"

class CameraControlSystem : public ecs::System {

private:

public:
    CameraControlSystem();
    void look(Shader& shader, vec3 cameraPos, vec3 cameraFront, vec3 cameraUp);
};

#endif