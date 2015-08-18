#include "VertexShader.hpp"

VertexShader::VertexShader(string filename) : ShaderFile(filename) {
    setGLId(loadShader(filename));
    printErrors();
}

GLuint VertexShader::createShader() {
    return glCreateShader(GL_VERTEX_SHADER);
}
