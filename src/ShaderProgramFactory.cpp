#include "ShaderProgramFactory.hpp"

ShaderProgram ShaderProgramFactory::createShaderProgram(string vertex_shader_filename, string fragment_shader_filename) {

    ShaderFile vertex_shader(vertex_shader_filename, VertexShaderCreator());
    ShaderFile fragment_shader(fragment_shader_filename, FragmentShaderCreator());


    return ShaderProgram(vertex_shader, fragment_shader);

}
