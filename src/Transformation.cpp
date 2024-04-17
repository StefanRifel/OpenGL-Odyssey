#include "utils/Transformation.hpp"
#include <iostream>
#include <cmath>

void Transformation::identity(mat4& out) {
    for (int x = 0; x < MAT_N; x++) {
        for (int y = 0; y < MAT_N; y++) {
            x == y ? out[x][y] = 1.0f : out[x][y] = 0.0f;
        }
    }
}

mat4 Transformation::translate(mat4& in, vec3& v) {
    /*
        create translation Matrix:
        | 1  0  0 Tx |
        | 0  1  0 Ty |
        | 0  0  1 Tz |
        | 0  0  0  1 |
    */
    mat4 translationMatrix {1.0f};
    translationMatrix[0][3] = v.x();  
    translationMatrix[1][3] = v.y();
    translationMatrix[2][3] = v.z();

    return in * translationMatrix;
}

mat4 Transformation::scale(mat4& in, vec3& v) {
    /*
        create scale Matrix:
        | S1   0   0   0 |
        |  0  S2   0   0 |
        |  0   0  S3   0 |
        |  0   0   0   1 |
    */
    mat4 scaleMatrix {1.0f};
    scaleMatrix[0][0] = v.x();  
    scaleMatrix[1][1] = v.y();
    scaleMatrix[2][2] = v.z();

    return in * scaleMatrix;
}

mat4 Transformation::rotateZ(mat4& in, GLuint angle) {
    /*
        create rotate Z Matrix:
        | cos -sin    0    0   |
        | sin  cos    0    0   |
        |   0    0    0    0   |
        |   0    0    0    1   |
    */
    mat4 rotateZMatrix {1.0f};
    float radiant = angle * M_PI /180;
    rotateZMatrix[0][0] = cos(radiant);  
    rotateZMatrix[0][1] = -sin(radiant);
    rotateZMatrix[1][0] = sin(radiant);
    rotateZMatrix[1][1] = cos(radiant);

    return in * rotateZMatrix;
}

mat4 Transformation::rotateX(mat4& in, GLuint angle) {
    /*
        create rotate X Matrix:
        |   0    0    0    0   |
        |   0  cos -sin    0   |
        |   0  sin  cos    0   |
        |   0    0    0    1   |
    */
    mat4 rotateXMatrix {1.0f};
    float radiant = angle * M_PI /180;
    rotateXMatrix[1][1] = cos(radiant);  
    rotateXMatrix[1][2] = -sin(radiant);
    rotateXMatrix[2][1] = sin(radiant);
    rotateXMatrix[2][2] = cos(radiant);

    return in * rotateXMatrix;
}

mat4 Transformation::rotateY(mat4& in, GLuint angle) {
    /*
        create rotate Z Matrix:
        | cos    0 -sin    0   |
        |   0    0    0    0   |
        |-sin    0  cos    0   |
        |   0    0    0    1   |
    */
    mat4 rotateYMatrix {1.0f};
    float radiant = angle * M_PI /180;
    rotateYMatrix[0][0] = cos(radiant);  
    rotateYMatrix[0][2] = sin(radiant);
    rotateYMatrix[2][0] = -sin(radiant);
    rotateYMatrix[2][2] = cos(radiant);

    return in * rotateYMatrix;
}

void Transformation::lookAt() {
GLfloat look[] = {0.0f, 0.0f, 0.0f};
GLfloat eye[] = {0.0f, 0.0f, 0.0f};
GLfloat up[] = {0.0f, 1.0f, 0.0f};

GLfloat n[] = {eye[0] - look[0], eye[1] - look[1], eye[2] - look[2]};
//GLfloat u[] = 

}
