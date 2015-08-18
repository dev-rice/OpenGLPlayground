#include "VertexShaderCreator.hpp"

GLuint VertexShaderCreator::create() {
    return glCreateShader(GL_VERTEX_SHADER);
}
