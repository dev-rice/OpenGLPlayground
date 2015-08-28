#include "ShaderProgramFactory.hpp"

ShaderProgram ShaderProgramFactory::createShaderProgram(string vertex_shader_filename, string fragment_shader_filename) {

    ShaderFile vertex_shader(vertex_shader_filename, make_unique<VertexShaderCreator>());
    ShaderFile fragment_shader(fragment_shader_filename, make_unique<FragmentShaderCreator>());

    return ShaderProgram(vertex_shader, fragment_shader);

}
