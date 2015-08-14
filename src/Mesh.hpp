#ifndef Mesh_h
#define Mesh_h

#include <iostream>

#include "includes/gl.hpp"
#include "includes/glm.hpp"

#include "Shader.hpp"

using namespace std;

class Mesh {
public:
    Mesh();
    void draw();
    void clearBuffer();
    void show();
    void hide();
    void toggleVisibility();
    bool isHidden();
private:
    void linkMeshToShader(GLuint shader_program);

    bool is_hidden;
    Shader shader;
};

#endif
