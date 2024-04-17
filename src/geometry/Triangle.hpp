#ifndef TRIANGLE_HH
#define TRIANGLE_HH

#include "RenderableObject.hpp"

class Triangle : public RenderableObject{

private:

public:
    Triangle();
    Triangle(std::vector<Vertex> vertices);
    Triangle(std::vector<Vertex> vertices, vec3 color);
    virtual ~Triangle() override;
    virtual void draw(Shader shader) const override;
};

#endif