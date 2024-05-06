#ifndef RENDERABLE_HH
#define RENDERABLE_HH

#include "../libs/SMath/include/vec3.hpp"

namespace ecs {
    
    struct Renderable {
        vec3 position;
        vec3 rotation;
        vec3 scale;
    };
}

#endif