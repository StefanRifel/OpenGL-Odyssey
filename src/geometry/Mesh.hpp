#ifndef MESH_HH
#define MESH_HH

#include "RenderableObject.hpp"
#include "../utils/vec3.hpp"

class Mesh : public RenderableObject {
private:
    
public:
    Mesh();
    Mesh(std::vector<Vertex> vertices);
    Mesh(std::vector<Vertex> vertices, std::vector<GLuint> indices);
    virtual ~Mesh() override;
    virtual void draw(Shader shader) const override;
};

#endif