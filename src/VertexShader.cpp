#include "VertexShader.hpp"

VertexShader::VertexShader(string filename) : ShaderFile(filename) {
    setGLId(loadShader(filename));
}

GLuint VertexShader::loadShader(string vs_filename){
    // Create the vertex shader
    GLuint vertex_shader = glCreateShader(GL_VERTEX_SHADER);

    string vs_source = getFileContents(vs_filename);
    const char* vs_source_c = vs_source.c_str();

    glShaderSource(vertex_shader, 1, &vs_source_c, NULL);

    // Compile it
    glCompileShader(vertex_shader);

    cout << "Error compiling shader: " << getShaderErrorLog() << "\n";

    return vertex_shader;
}
