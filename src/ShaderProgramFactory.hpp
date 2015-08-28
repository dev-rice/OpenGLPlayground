#ifndef ShaderProgramFactory_h
#define ShaderProgramFactory_h

#include <string>
#include <iostream>
#include <memory>

#include "VertexShaderCreator.hpp"
#include "FragmentShaderCreator.hpp"
#include "ShaderFile.hpp"
#include "ShaderProgram.hpp"

using namespace std;

class ShaderProgramFactory {
public:
    ShaderProgram createShaderProgram(string vertex_shader_filename, string fragment_shader_filename);

private:

};

#endif
