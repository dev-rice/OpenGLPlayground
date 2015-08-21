#ifndef FlatMesh_h
#define FlatMesh_h

#include "includes/gl.hpp"

#include <vector>

#include "VertexAttribute.hpp"
#include "ShaderProgram.hpp"

class FlatMesh {
public:
    FlatMesh(vector<VertexAttribute>& vertex_attributes);

    void draw();
    void prepareToBeDrawn();
    void drawOutline();
    void linkToShader(ShaderProgram& shader_program);

    int getNumberOfTriangles();

protected:
    void bindVAO();
    void createVAO();
    void createVBO(vector<GLfloat>& vertices);
    void createEBO(vector<GLuint>& elements);

    void setNumberOfElements(int number_of_elements);
    int getNumberOfElements();

    int getVertexWidth();
    void specifyVertexAttribute(GLint attribute_location, int attribute_width, int offset, int vertex_width);

    void drawAllElements();

    vector<VertexAttribute>& getVertexAttributes();

    GLuint vao;
    GLuint vbo;
    int number_of_elements;

    vector<VertexAttribute>* vertex_attributes;


};

#endif
