#ifndef TRANSFORMATION_HH
#define TRANSFORMATION_HH

#include <GL/glew.h>
#include <string>

class Transformation {
private:

public:
    // It is advised to first do scaling operations, then rotations and lastly translations
    // when combining matrices otherwise they may (negatively) affect each other.
    static void identity(GLfloat* matrix);
    static void translate(GLfloat* out, GLfloat* in, GLfloat* v);
    static void scale(GLfloat* out, GLfloat* in, GLfloat* v);
    static void rotateZ(GLfloat* out, GLfloat* in, GLuint angle);
    static void rotateX(GLfloat* out, GLfloat* in, GLuint angle);
    static void rotateY(GLfloat* out, GLfloat* in, GLuint angle);
    static void printM4x4(GLfloat* matrix, std::string name);
    static void printM(GLfloat* matrix, std::string name);
    static void lookAt();
};

#endif