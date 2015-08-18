#include "FragmentShaderCreator.hpp"

GLuint FragmentShaderCreator::create() {
    cout << "Creating Fragment Shader\n";
    return glCreateShader(GL_FRAGMENT_SHADER);
}
