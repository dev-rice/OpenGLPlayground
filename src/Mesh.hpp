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
    Mesh();

    void draw();
    void prepareToBeDrawn();
    void linkToShader(ShaderProgram& shader_program);

    void show();
    void hide();
    void toggleVisibility();
    bool isHidden();


private:
    void bindVAO();
    void createVAO();
    void createVBO();
    void createEBO();
    vector<GLfloat> getVertices();
    vector<GLuint> getElements();
    int getNumElements();

    void drawAllElements();

    bool is_hidden;

    GLuint vao;
};

#endif
