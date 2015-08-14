#include "ShaderFile.hpp"

ShaderFile::ShaderFile(string filename) {

}

GLuint ShaderFile::getGLId() {
    return shader_id;
}

void ShaderFile::setGLId(GLuint id) {
    shader_id = id;
}

string ShaderFile::getShaderErrorLog() {
    string error_log = "";
    GLint status;
    glGetShaderiv(getGLId(), GL_COMPILE_STATUS, &status);
    if (status != GL_TRUE){
        char info_log[512] = "";
        glGetShaderInfoLog(getGLId(), 512, NULL, info_log);
        error_log = info_log;
    }
    return error_log;
}

string ShaderFile::getFileContents(string filename) {
    ifstream input_stream(filename);
    string contents((istreambuf_iterator<char>(input_stream)), istreambuf_iterator<char>());
    return contents;
}
