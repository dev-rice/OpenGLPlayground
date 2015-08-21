#include "VertexAttribute.hpp"

VertexAttribute::VertexAttribute(string name, int width, int offset) : name(name), width(width), offset(offset) {

}

void VertexAttribute::attachToShader(ShaderProgram& shader_program, int vertex_width) {

    specifyVertexAttribute(getLocationInShader(shader_program), getWidth(), getOffset(), vertex_width);
}

void VertexAttribute::specifyVertexAttribute(GLint attribute_location, int attribute_width, int offset, int vertex_width) {

    glEnableVertexAttribArray(attribute_location);

    int width_in_bytes = vertex_width * sizeof(GLfloat);
    int offset_in_bytes = offset * sizeof(GLfloat);

    glVertexAttribPointer(attribute_location, attribute_width, GL_FLOAT, GL_FALSE, vertex_width * sizeof(GLfloat), (void*)(offset * sizeof(GLfloat)));

}

GLint VertexAttribute::getLocationInShader(ShaderProgram& shader_program) {
    return shader_program.getAttributeLocation(getName());
}

string VertexAttribute::getName() {
    return name;
}

int VertexAttribute::getWidth() {
    return width;
}

int VertexAttribute::getOffset() {
    return offset;
}
