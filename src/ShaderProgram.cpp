#include "ShaderProgram.hpp"

ShaderProgram::ShaderProgram(){
    gl_shader_id = 0;
}

ShaderProgram::ShaderProgram(ShaderFile& vertex_shader, ShaderFile& fragment_shader) {

    gl_shader_id = glCreateProgram();

    combineShaderPrograms(vertex_shader, fragment_shader);
    bindFragmentDataLocation();
    link();
}

GLuint ShaderProgram::getGLId() {
    return gl_shader_id;
}

void ShaderProgram::use() {
    glUseProgram(getGLId());
}

GLint ShaderProgram::getUniformLocation(string uniform_name) {
    return glGetUniformLocation(getGLId(), uniform_name.c_str());
}

GLint ShaderProgram::getAttributeLocation(string attribute_name) {
    return glGetAttribLocation(getGLId(), attribute_name.c_str());
}

void ShaderProgram::combineShaderPrograms(ShaderFile& vertex_shader, ShaderFile& fragment_shader) {

    vertex_shader.attachTo(gl_shader_id);
    fragment_shader.attachTo(gl_shader_id);

}

void ShaderProgram::bindFragmentDataLocation() {
    glBindFragDataLocation(gl_shader_id, 0, "outColor");
}

void ShaderProgram::link() {
    glLinkProgram(gl_shader_id);
}
