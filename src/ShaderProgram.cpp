#include "ShaderProgram.hpp"

ShaderProgram::ShaderProgram(){
    gl_shader_id = 0;
}

ShaderProgram::ShaderProgram(VertexShader& vertex_shader, FragmentShader& fragment_shader) {

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

void ShaderProgram::combineShaderPrograms(VertexShader& vertex_shader, FragmentShader& fragment_shader) {

    vertex_shader.attachTo(gl_shader_id);
    fragment_shader.attachTo(gl_shader_id);

}

void ShaderProgram::bindFragmentDataLocation() {
    glBindFragDataLocation(gl_shader_id, 0, "outColor");
}

void ShaderProgram::link() {
    glLinkProgram(gl_shader_id);
}
