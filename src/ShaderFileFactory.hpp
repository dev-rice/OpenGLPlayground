#ifndef ShaderFileFactory_h
#define ShaderFileFactory_h

#include <string>

#include "ShaderFile.hpp"
#include "VertexShaderCreator.hpp"
#include "FragmentShaderCreator.hpp"

using namespace std;

class ShaderFileFactory {
public:
    ShaderFile createShaderFile(string filename);

private:

    ShaderCreator& getCorrectCreator(string filename);

    string lastCharacters(string input, int num);

    VertexShaderCreator vertex_shader_creator;
    FragmentShaderCreator fragment_shader_creator;

};

#endif
