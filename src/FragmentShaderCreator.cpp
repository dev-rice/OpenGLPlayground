#include "FragmentShaderCreator.hpp"

GLuint FragmentShaderCreator::create() {
    return glCreateShader(GL_FRAGMENT_SHADER);
}
