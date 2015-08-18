#ifndef Mesh_h
#define Mesh_h

#include <iostream>
#include <vector>

#include "includes/gl.hpp"
#include "includes/glm.hpp"

#include "ShaderProgram.hpp"
#include "MeshLoader.hpp"

using namespace std;

class Mesh {
public:
    Mesh(MeshLoader& mesh_loader);

    void draw();
    void prepareToBeDrawn();
    void linkToShader(ShaderProgram& shader_program);

    void show();
    void hide();
    void toggleVisibility();
    bool isHidden();

    MeshLoader& getMeshLoader();

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
    MeshLoader* mesh_loader;
};

#endif
