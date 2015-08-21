#ifndef VertexSpecification_h
#define VertexSpecification_h

#include <vector>

#include "VertexAttribute.hpp"
#include "ShaderProgram.hpp"

class VertexSpecification {
public:
    VertexSpecification();

    void attachToShader(ShaderProgram& shader_program);
    void addAttribute(VertexAttribute attribute);
    int getVertexWidth();
private:

    vector<VertexAttribute>& getVertexAttributes();

    vector<VertexAttribute> vertex_attributes;
};

#endif
