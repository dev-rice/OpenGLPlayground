#ifndef Mesh_h
#define Mesh_h

#include <iostream>
#include <vector>

#include "includes/gl.hpp"
#include "includes/glm.hpp"

#include "ShaderProgram.hpp"

using namespace std;

class Mesh {
public:
    Mesh(ShaderProgram& shader);

    void clearBuffers();
    void draw();

    void show();
    void hide();
    void toggleVisibility();
    bool isHidden();

    ShaderProgram& getShaderProgram();

    void bindVAO();
    void prepareToBeDrawn();

private:
    void createVAO();
    void createVBO();
    void createEBO();
    vector<GLfloat> getVertices();
    vector<GLuint> getElements();
    int getNumElements();

    void drawAllElements();
    void linkMeshToShader(ShaderProgram& shader_program);

    bool is_hidden;
    ShaderProgram* shader;

    GLuint vao;
};

#endif
