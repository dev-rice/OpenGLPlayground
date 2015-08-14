#include "shader.hpp"

Shader::Shader(){
    gl_shader_id = 0;
}

Shader::Shader(GLuint shader){
    gl_shader_id = shader;
}

Shader::Shader(string vs_filename, string fs_filename) {
    gl_shader_id = loadShaderProgram(vs_filename, fs_filename);
}

GLuint Shader::getGLId() {
    return gl_shader_id;
}

void Shader::use() {
    glUseProgram(getGLId());

}

string Shader::getFileContents(string filename) {
    ifstream input_stream(filename);
    string contents((istreambuf_iterator<char>(input_stream)), istreambuf_iterator<char>());
    // cout << contents;
    return contents;
}

GLuint Shader::combineShaderProgram(GLuint vertex_shader, GLuint fragment_shader) {
    // Combine the shaders into a single program
    GLuint shader_program = glCreateProgram();
    glAttachShader(shader_program, vertex_shader);
    glAttachShader(shader_program, fragment_shader);

    // Tell the OpenGL to use the variable outColor for its output
    glBindFragDataLocation(shader_program, 0, "outColor");

    // Put the shader on the graphics card.
    glLinkProgram(shader_program);

    return shader_program;
}

GLuint Shader::loadShaderProgram(string vs_filename, string fs_filename) {
    GLuint shader_program;

    VertexShader vertex_shader(vs_filename);
    FragmentShader fragment_shader(fs_filename);
    shader_program = combineShaderProgram(vertex_shader.getGLId(), fragment_shader.getGLId());

    return shader_program;
}
