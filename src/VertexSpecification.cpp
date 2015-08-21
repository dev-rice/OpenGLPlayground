#include "VertexSpecification.hpp"

VertexSpecification::VertexSpecification() {

}

void VertexSpecification::attachToShader(ShaderProgram& shader_program) {
    for (VertexAttribute& vertex_attribute : getVertexAttributes()) {
        vertex_attribute.attachToShader(shader_program, getVertexWidth());
    }
}

void VertexSpecification::addAttribute(VertexAttribute attribute) {
    vertex_attributes.push_back(attribute);
}

int VertexSpecification::getVertexWidth() {
    int width = 0;
    for (VertexAttribute& vertex_attribute : getVertexAttributes()) {
        width += vertex_attribute.getWidth();
    }
    return width;
}

vector<VertexAttribute>& VertexSpecification::getVertexAttributes() {
    return vertex_attributes;
}
