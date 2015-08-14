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

GLuint Shader::loadVertexShader(string vs_filename){
    // Create the vertex shader
    GLuint vertex_shader = glCreateShader(GL_VERTEX_SHADER);

    string vs_source = getFileContents(vs_filename);
    const char* vs_source_c = vs_source.c_str();

    glShaderSource(vertex_shader, 1, &vs_source_c, NULL);

    // Compile it
    glCompileShader(vertex_shader);

    cout << getShaderErrorLog(vertex_shader);

    return vertex_shader;
}

GLuint Shader::loadFragmentShader(string fs_filename){
    string fs_source = getFileContents(fs_filename);
    const char* fs_source_c = fs_source.c_str();

    // Create the fragment shader
    GLuint fragment_shader = glCreateShader(GL_FRAGMENT_SHADER);

    glShaderSource(fragment_shader, 1, &fs_source_c, NULL);

    // Compile it
    glCompileShader(fragment_shader);

    cout << getShaderErrorLog(fragment_shader);

    return fragment_shader;
}

string Shader::getShaderErrorLog(GLuint shader_id) {
    string error_log = "";
    GLint status;
    glGetShaderiv(shader_id, GL_COMPILE_STATUS, &status);
    if (status != GL_TRUE){
        char info_log[512];
        glGetShaderInfoLog(shader_id, 512, NULL, info_log);
        error_log = info_log;
    }
    return error_log;
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

    // Tell the fragment shader to use the variable outColor for its output
    glBindFragDataLocation(shader_program, 0, "outColor");

    // Put the shader on the graphics card.
    glLinkProgram(shader_program);

    // Free up the space from the vetex and fragment shader because
    // they have been combined into the shader program.
    glDeleteShader(vertex_shader);
    glDeleteShader(fragment_shader);

    return shader_program;
}

GLuint Shader::loadShaderProgram(string vs_filename, string fs_filename) {
    GLuint shader_program;

    GLuint vertex_shader = loadVertexShader(vs_filename);
    GLuint fragment_shader = loadFragmentShader(fs_filename);
    shader_program = combineShaderProgram(vertex_shader, fragment_shader);

    return shader_program;
}
