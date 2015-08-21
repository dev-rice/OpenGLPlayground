#ifndef VertexAttribute_h
#define VertexAttribute_h

#include <string>

#include "includes/gl.hpp"

#include "ShaderProgram.hpp"

using namespace std;

class VertexAttribute {
public:
    VertexAttribute(string name, int width, int offset);

    void attachToShader(ShaderProgram& shader_program, int vertex_width);

    string getName();
    int getWidth();
    int getOffset();

private:
    void specifyVertexAttribute(GLint attribute_location, int attribute_width, int offset, int vertex_width);

    GLint getLocationInShader(ShaderProgram& shader_program);

    string name;
    int width;
    int offset;
};

#endif
