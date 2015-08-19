#include "ShaderFileFactory.hpp"

ShaderFile ShaderFileFactory::createShaderFile(string filename) {
    return ShaderFile(filename, getCorrectCreator(filename));
}

ShaderCreator& ShaderFileFactory::getCorrectCreator(string filename) {
    string file_extension = lastCharacters(filename, 3);

    if (file_extension == ".vs") {
        return vertex_shader_creator;
    } else if (file_extension == ".fs") {
        return fragment_shader_creator;
    }
}

string ShaderFileFactory::lastCharacters(string input, int num) {
    return input.substr(input.size() - num);
}
