#ifndef Shader_h
#define Shader_h

#include <string>
#include <fstream>
#include <iostream>

#include "includes/gl.hpp"

#include "VertexShader.hpp"
#include "FragmentShader.hpp"

using namespace std;

class ShaderProgram {
public:
    ShaderProgram();
    ShaderProgram(VertexShader& vertex_shader, FragmentShader& fragment_shader);

    GLuint getGLId();
    void use();

private:

    GLuint combineShaderProgram(VertexShader& vertex_shader, FragmentShader& fragment_shader);

    GLuint gl_shader_id;

};

#endif
