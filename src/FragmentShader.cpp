#include "FragmentShader.hpp"

FragmentShader::FragmentShader(string filename) : ShaderFile(filename) {
    setGLId(loadShader(filename));
    printErrors();
}

GLuint FragmentShader::loadShader(string fs_filename){
    string fs_source = getFileContents(fs_filename);
    const char* fs_source_c = fs_source.c_str();

    // Create the fragment shader
    GLuint fragment_shader = glCreateShader(GL_FRAGMENT_SHADER);

    glShaderSource(fragment_shader, 1, &fs_source_c, NULL);

    // Compile it
    glCompileShader(fragment_shader);

    return fragment_shader;
}
