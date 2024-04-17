#ifndef TRANSFORMATION_HH
#define TRANSFORMATION_HH

#include <GL/glew.h>
#include <string>
#include "mat4.hpp"
#include "vec3.hpp"

class Transformation {
private:

public:
    // It is advised to first do scaling operations, then rotations and lastly translations
    // when combining matrices otherwise they may (negatively) affect each other.
    static void identity(mat4& matrix);
    static mat4 translate(mat4& in, vec3& v);
    static mat4 scale(mat4& in, vec3& v);
    // Rotate in this order: Rx , Ry , Rz
    // to prevent Gimbal lock
    static mat4 rotateZ(mat4& in, GLuint angle);
    static mat4 rotateX(mat4& in, GLuint angle);
    static mat4 rotateY(mat4& in, GLuint angle);
    static void lookAt();
};

#endif