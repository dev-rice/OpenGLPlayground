#include "FragmentShader.hpp"

FragmentShader::FragmentShader(string filename) : ShaderFile(filename) {
    setGLId(loadShader(filename));
    printErrors();
}

GLuint FragmentShader::createShader() {
    return glCreateShader(GL_FRAGMENT_SHADER);
}
