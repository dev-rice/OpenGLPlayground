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
    GLint getUniformLocation(string uniform_name);

private:

    void combineShaderPrograms(VertexShader& vertex_shader, FragmentShader& fragment_shader);
    void bindFragmentDataLocation();
    void link();

    GLuint gl_shader_id;

};

#endif
