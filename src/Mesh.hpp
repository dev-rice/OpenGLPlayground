#ifndef Mesh_h
#define Mesh_h

#include <iostream>
#include <vector>

#include "includes/gl.hpp"
#include "includes/glm.hpp"

#include "ShaderProgram.hpp"
#include "MeshFileParser.hpp"

using namespace std;

class Mesh {
public:
    Mesh(MeshFileParser& mesh_file_parser);

    void draw();
    void prepareToBeDrawn();
    void linkToShader(ShaderProgram& shader_program);

    void show();
    void hide();
    void toggleVisibility();
    bool isHidden();

    MeshFileParser& getMeshFileParser();

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
    MeshFileParser* mesh_file_parser;
};

#endif
