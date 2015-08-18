#include "VertexShaderCreator.hpp"

GLuint VertexShaderCreator::create() {
    cout << "Creating Vertex Shader\n";
    return glCreateShader(GL_VERTEX_SHADER);
}
