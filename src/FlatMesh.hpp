#ifndef FlatMesh_h
#define FlatMesh_h

#include "includes/gl.hpp"

#include <vector>

#include "ShaderProgram.hpp"

class FlatMesh {
public:
    FlatMesh();

    void draw();
    void prepareToBeDrawn();
    void drawOutline();
    void linkToShader(ShaderProgram);

    int getNumberOfTriangles();

protected:
    void bindVAO();
    void createVAO();
    void createVBO(vector<GLfloat>& vertices);
    void createEBO(vector<GLuint>& elements);

    void setNumberOfElements(int number_of_elements);
    int getNumberOfElements();

    void drawAllElements();

    GLuint vao;
    int number_of_elements;

};

#endif