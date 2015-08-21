#ifndef Mesh_h
#define Mesh_h

#include <iostream>

#include "includes/gl.hpp"
#include "includes/glm.hpp"

#include "ShaderProgram.hpp"
#include "MeshFileParser.hpp"
#include "VertexSpecification.hpp"

using namespace std;

class Mesh {
public:
    Mesh(VertexSpecification& vertex_specification);
    Mesh(string filename, MeshFileParser& mesh_file_parser, VertexSpecification& vertex_specification);

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

    VertexSpecification& getVertexSpecification();

    GLuint vao;
    int number_of_elements;

    VertexSpecification* vertex_specification;
};

#endif
