#include "FragmentShader.hpp"

FragmentShader::FragmentShader(string filename) {
    shader_id = loadFragmentShader(filename);
}

GLuint FragmentShader::getGLId() {
    return shader_id;
}

GLuint FragmentShader::loadFragmentShader(string fs_filename){
    string fs_source = getFileContents(fs_filename);
    const char* fs_source_c = fs_source.c_str();

    // Create the fragment shader
    GLuint fragment_shader = glCreateShader(GL_FRAGMENT_SHADER);

    glShaderSource(fragment_shader, 1, &fs_source_c, NULL);

    // Compile it
    glCompileShader(fragment_shader);

    cout << getShaderErrorLog();

    return fragment_shader;
}

string FragmentShader::getShaderErrorLog() {
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

string FragmentShader::getFileContents(string filename) {
    ifstream input_stream(filename);
    string contents((istreambuf_iterator<char>(input_stream)), istreambuf_iterator<char>());
    // cout << contents;
    return contents;
}
