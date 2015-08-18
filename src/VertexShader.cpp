#include "VertexShader.hpp"

VertexShader::VertexShader(string filename) : ShaderFile(filename) {
    setGLId(loadShader(filename));
    printErrors();
}

GLuint VertexShader::createShader() {
    return glCreateShader(GL_VERTEX_SHADER);
}

GLuint VertexShader::loadShader(string filename){
    GLuint shader = createShader();

    string contents = getFileContents(filename);
    const char* contents_as_cstr = contents.c_str();

    glShaderSource(shader, 1, &contents_as_cstr, NULL);

    // Compile it
    glCompileShader(shader);

    return shader;
}
