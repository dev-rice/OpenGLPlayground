#ifndef Shader_h
#define Shader_h

#include <string>
#include <fstream>
#include <iostream>

#include "includes/gl.hpp"

#include "ShaderFile.hpp"

using namespace std;

class ShaderProgram {
public:
    ShaderProgram();
    ShaderProgram(ShaderFile& vertex_shader, ShaderFile& fragment_shader);

    void use();
    GLint getUniformLocation(string uniform_name);
    GLint getAttributeLocation(string attribute_name);

    GLuint getGLId();

private:

    void combineShaderPrograms(ShaderFile& vertex_shader, ShaderFile& fragment_shader);
    void bindFragmentDataLocation();
    void link();

    GLuint gl_shader_id;

};

#endif
