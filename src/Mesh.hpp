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
    Mesh(string filename, MeshFileParser& mesh_file_parser);

    void draw();
    void prepareToBeDrawn();
    void linkToShader(ShaderProgram& shader_program);

    int getNumberOfTriangles();

private:
    void bindVAO();
    void createVAO();
    void createVBO(vector<GLfloat>& vertices);
    void createEBO(vector<GLuint>& elements);
    void sendMeshDataToOpenGL(MeshFileParser& mesh_file_parser);
    void setMeshStatsFromParser(MeshFileParser& mesh_file_parser);

    void setNumberOfElements(int number_of_elements);
    int getNumberOfElements();

    void drawAllElements();

    GLuint vao;
    int number_of_elements;
};

#endif
