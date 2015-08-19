#include "ShaderFileFactory.hpp"

ShaderFile ShaderFileFactory::createShaderFile(string filename) {
    return ShaderFile(filename, getCorrectCreator(filename));
}

ShaderCreator& ShaderFileFactory::getCorrectCreator(string filename) {
    string last_three_chars = lastCharacters(filename, 3);

    if (last_three_chars == ".vs") {
        return vertex_shader_creator;
    } else if (last_three_chars == ".fs") {
        return fragment_shader_creator;
    }
}

string ShaderFileFactory::lastCharacters(string input, int num) {
    return input.substr(input.size() - num);
}
