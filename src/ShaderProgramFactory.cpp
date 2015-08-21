#include "ShaderProgramFactory.hpp"

ShaderProgram ShaderProgramFactory::createShaderProgram(string vertex_shader_filename, string fragment_shader_filename) {

    ShaderFile vertex_shader(vertex_shader_filename, vertex_shader_creator);
    ShaderFile fragment_shader(fragment_shader_filename, fragment_shader_creator);


    return ShaderProgram(vertex_shader, fragment_shader);

}
