#ifndef CIRCLE_HH
#define CIRCLE_HH

#include "RenderableObject.hpp"

class Circle : public RenderableObject {
private:

public:
    Circle(std::vector<Vertex> vertices);
    virtual ~Circle() override;
    virtual void draw(Shader shader) const override;
};

#endif