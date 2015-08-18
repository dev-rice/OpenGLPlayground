#include "VertexShader.hpp"

VertexShader::VertexShader(string filename) : ShaderFile(filename) {
    setGLId(loadShader(filename));
    printErrors();
}

GLuint VertexShader::loadShader(string filename){
    // Create the vertex shader
    GLuint shader = glCreateShader(GL_VERTEX_SHADER);

    string contents = getFileContents(filename);
    const char* contents_as_cstr = contents.c_str();

    glShaderSource(shader, 1, &contents_as_cstr, NULL);

    // Compile it
    glCompileShader(shader);

    return shader;
}
