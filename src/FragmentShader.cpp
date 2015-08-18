#include "FragmentShader.hpp"

FragmentShader::FragmentShader(string filename) : ShaderFile(filename) {
    setGLId(loadShader(filename));
    printErrors();
}

GLuint FragmentShader::createShader() {
    return glCreateShader(GL_FRAGMENT_SHADER);
}

GLuint FragmentShader::loadShader(string filename){
    GLuint shader = createShader();

    string contents = getFileContents(filename);
    const char* contents_as_cstr = contents.c_str();

    glShaderSource(shader, 1, &contents_as_cstr, NULL);

    // Compile it
    glCompileShader(shader);

    return shader;
}
