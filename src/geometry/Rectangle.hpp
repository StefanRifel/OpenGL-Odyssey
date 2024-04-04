#include "RenderableObject.hpp"

#ifndef RECTANGLE_HH
#define  RECTANGLE_HH

class Rectangle : public RenderableObject{
private:
    
public:
    Rectangle();
    Rectangle(std::vector<Vertex> vertices, std::vector<GLuint> indices);
    ~Rectangle();
    virtual void draw(Shader shader) const override;
};

#endif