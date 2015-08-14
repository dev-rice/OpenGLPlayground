#include "ShaderProgram.hpp"

ShaderProgram::ShaderProgram(){
    gl_shader_id = 0;
}

ShaderProgram::ShaderProgram(VertexShader& vertex_shader, FragmentShader& fragment_shader) {
    gl_shader_id = combineShaderProgram(vertex_shader, fragment_shader);
}

GLuint ShaderProgram::getGLId() {
    return gl_shader_id;
}

void ShaderProgram::use() {
    glUseProgram(getGLId());
}

GLuint ShaderProgram::combineShaderProgram(VertexShader& vertex_shader, FragmentShader& fragment_shader) {
    // Combine the shaders into a single program
    GLuint shader_program = glCreateProgram();
    vertex_shader.attachTo(shader_program);
    fragment_shader.attachTo(shader_program);

    // Tell the OpenGL to use the variable outColor for its output
    glBindFragDataLocation(shader_program, 0, "outColor");

    // Put the shader on the graphics card.
    glLinkProgram(shader_program);

    return shader_program;
}
