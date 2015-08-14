#include "ShaderFile.hpp"

ShaderFile::ShaderFile(string filename) {

}

ShaderFile::~ShaderFile() {
    glDeleteShader(getGLId());
}

GLuint ShaderFile::getGLId() {
    return shader_id;
}

void ShaderFile::setGLId(GLuint id) {
    shader_id = id;
}

void ShaderFile::attachTo(GLuint shader_program) {
    glAttachShader(shader_program, getGLId());
}

string ShaderFile::getErrorLog() {
    char info_log[512] = "";

    if (hasErrors()){
        glGetShaderInfoLog(getGLId(), 512, NULL, info_log);
    }

    return string(info_log);
}

bool ShaderFile::hasErrors() {
    GLint status;
    glGetShaderiv(getGLId(), GL_COMPILE_STATUS, &status);
    return status != GL_TRUE;
}

string ShaderFile::getFileContents(string filename) {
    ifstream input_stream(filename);
    string contents((istreambuf_iterator<char>(input_stream)), istreambuf_iterator<char>());
    return contents;
}

void ShaderFile::printErrors() {
    if (hasErrors()) {
        cout << "Error compiling shader: \n" << getErrorLog() << "\n";
    }
}
