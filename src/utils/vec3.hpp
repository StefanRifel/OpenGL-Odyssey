#ifndef VEC3_HH
#define VEC3_HH

const int N = 3;

#include <iostream>
#include <array>

class vec3
{
private:
    std::array<float, 3> vector;
public:
    vec3();
    vec3(float x, float y, float z);
    vec3(const vec3& v);
    ~vec3();

    float x();
    float y();
    float z();

    friend std::ostream& operator<< (std::ostream& out, const vec3& v);

    vec3& operator= (const vec3& v);
    float& operator[] (int index);

    vec3 operator+ (const vec3& v) const;
    vec3 operator+= (const vec3& v);

    vec3 operator- (const vec3& v) const;
    vec3 operator-= (const vec3& v);

    vec3 operator* (const float a) const;
};

#endif