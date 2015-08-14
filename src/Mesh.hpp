#ifndef Mesh_h
#define Mesh_h

#include <iostream>

#include "includes/gl.hpp"
#include "includes/glm.hpp"

#include "ShaderProgram.hpp"

using namespace std;

class Mesh {
public:
    Mesh(ShaderProgram& shader);
    void draw();
    void clearBuffer();
    void show();
    void hide();
    void toggleVisibility();
    bool isHidden();
    ShaderProgram& getShaderProgram();

private:
    void linkMeshToShader(ShaderProgram& shader_program);
    bool is_hidden;
    ShaderProgram* shader;
};

#endif
