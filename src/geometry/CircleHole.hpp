#ifndef CIRCLEHOLE_HPP
#define CIRCLEHOLE_HPP

#include "RenderableObject.hpp"

class CircleHole : public RenderableObject {

private:
    
public:
    CircleHole(std::vector<Vertex> vertices);
    ~CircleHole();
    virtual void draw(Shader shader) const override;
};

#endif