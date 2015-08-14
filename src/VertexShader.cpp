#include "VertexShader.hpp"

VertexShader::VertexShader(string filename) {
    shader_id = loadVertexShader(filename);
}

GLuint VertexShader::getGLId() {
    return shader_id;
}

GLuint VertexShader::loadVertexShader(string vs_filename){
    // Create the vertex shader
    GLuint vertex_shader = glCreateShader(GL_VERTEX_SHADER);

    string vs_source = getFileContents(vs_filename);
    const char* vs_source_c = vs_source.c_str();

    glShaderSource(vertex_shader, 1, &vs_source_c, NULL);

    // Compile it
    glCompileShader(vertex_shader);

    cout << getShaderErrorLog();

    return vertex_shader;
}

string VertexShader::getShaderErrorLog() {
    string error_log = "";
    GLint status;
    glGetShaderiv(getGLId(), GL_COMPILE_STATUS, &status);
    if (status != GL_TRUE){
        char info_log[512];
        glGetShaderInfoLog(shader_id, 512, NULL, info_log);
        error_log = info_log;
    }
    return error_log;
}

string VertexShader::getFileContents(string filename) {
    ifstream input_stream(filename);
    string contents((istreambuf_iterator<char>(input_stream)), istreambuf_iterator<char>());
    // cout << contents;
    return contents;
}
