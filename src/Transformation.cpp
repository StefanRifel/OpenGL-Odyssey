#include "utils/Transformation.hpp"
#include <iostream>
#include <cmath>

void Transformation::identity(GLfloat* out) {
    int i = 0;
    for(GLfloat* ptr = out; ptr < out + 16; ptr++) {
        if(i % 5 == 0) {
            *ptr = 1.0f;
            i = 0;
        } else {
            *ptr = 0.0f;
        }
        i++;
    }
}

void Transformation::translate(GLfloat* out, GLfloat* in, GLfloat* v) {
    GLfloat translationMatrix[16];
    Transformation::identity(translationMatrix);
    translationMatrix[12] = v[0];  
    translationMatrix[13] = v[1];
    translationMatrix[14] = v[2];

    for (size_t y = 0; y < 4; y++) {
        for (size_t x = 0; x < 4; x++) {
            for (size_t i = 0; i < 4; i++) {
                out[y + (x * 4)] += translationMatrix[y + (i * 4)] * in[i +(x * 4)];
            }
        }
    }
}

void Transformation::scale(GLfloat* out, GLfloat* in, GLfloat* v) {
    GLfloat scaleMatrix[16];
    Transformation::identity(scaleMatrix);
    scaleMatrix[0] = v[0];  
    scaleMatrix[5] = v[1];
    scaleMatrix[10] = v[2];

    for (size_t y = 0; y < 4; y++) {
        for (size_t x = 0; x < 4; x++) {
            for (size_t i = 0; i < 4; i++) {
                out[y + (x * 4)] += scaleMatrix[y + (i * 4)] * in[i +(x * 4)];
            }
        }
    }
}

void Transformation::rotateZ(GLfloat* out, GLfloat* in, GLuint angle) {
    GLfloat rotateMatrix[16];
    Transformation::identity(rotateMatrix);
    GLfloat radiant = angle * M_PI /180;
    rotateMatrix[0] = cos(radiant);  
    rotateMatrix[1] = sin(radiant);
    rotateMatrix[4] = -sin(radiant);
    rotateMatrix[5] = cos(radiant);

    for (size_t y = 0; y < 4; y++) {
        for (size_t x = 0; x < 4; x++) {
            for (size_t i = 0; i < 4; i++) {
                out[y + (x * 4)] += rotateMatrix[y + (i * 4)] * in[i +(x * 4)];
            }   
        }
    }
}

void Transformation::printM4x4(GLfloat* matrix, std::string name) {
    std::cout << "\nMatrix: " << name << "\n" << std::endl;
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            std::cout << matrix[i + (j * 4)] << "\t";
        }
        std::cout << "\n";
    }
    std::cout << "\n";
}

void Transformation::printM(GLfloat* matrix, std::string name) {
    std::cout << "\nMatrix straight: " << name << std::endl;
    std::cout << matrix[0];
    for (int i = 1; i < 16; i++) {
        std::cout << ", " << matrix[i];
    }
    std::cout << "\n";
}