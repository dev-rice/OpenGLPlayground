#include "FlatMesh.hpp"

FlatMesh::FlatMesh(){
    std::vector<GLfloat> vertices = {
             -1.0f,  1.0f,  0.0f, 1.0f,
             -1.0f, -1.0f,  0.0f, 0.0f,
              1.0f,  1.0f,  1.0f, 1.0f,
              1.0f, -1.0f,  1.0f, 0.0f,

    };

    std::vector<GLuint> elements = {
            0, 2, 1,
            1, 2, 3,
    };
    setNumberOfElements(elements.size());

    createVAO();
    createVBO(vertices);
    createEBO(elements);

}

void FlatMesh::createVAO() {
    glGenVertexArrays(1, &vao);
    bindVAO();
}

void FlatMesh::prepareToBeDrawn() {
    bindVAO();
}

void FlatMesh::bindVAO(){
    glBindVertexArray(vao);
}

void FlatMesh::createVBO(vector<GLfloat>& vertices) {
    GLuint vbo;
    glGenBuffers(1, &vbo);

    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(GLfloat), vertices.data(), GL_STATIC_DRAW);
}

void FlatMesh::createEBO(vector<GLuint>& elements) {
    // Create an element array
    GLuint ebo;
    glGenBuffers(1, &ebo);

    // Create Element Buffer Object
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, elements.size() * sizeof(GLuint), elements.data(), GL_STATIC_DRAW);
}

void FlatMesh::draw(){
    drawAllElements();
}

void FlatMesh::drawAllElements() {
    glDrawElements(GL_TRIANGLES, getNumberOfElements(), GL_UNSIGNED_INT, 0);
}

void FlatMesh::drawOutline(){
    glDrawArrays(GL_LINE_LOOP, 0, 6);
}

void FlatMesh::linkToShader(ShaderProgram shader){
    // glBindVertexArray(vao);
    // glBindBuffer(GL_ARRAY_BUFFER, vbo);

    GLint posAttrib = shader.getAttributeLocation("position");
    glEnableVertexAttribArray(posAttrib);
    glVertexAttribPointer(posAttrib, 2, GL_FLOAT, GL_FALSE,
                           4*sizeof(float), 0);

    GLint texAttrib = shader.getAttributeLocation("texture_coordinates");
    glEnableVertexAttribArray(texAttrib);
    glVertexAttribPointer(texAttrib, 2, GL_FLOAT, GL_FALSE,
                           4*sizeof(float), (void*)(2*sizeof(float)));

}

int FlatMesh::getNumberOfTriangles() {
    return number_of_elements / 3;
}

int FlatMesh::getNumberOfElements() {
    return number_of_elements;
}

void FlatMesh::setNumberOfElements(int number_of_elements) {
    this->number_of_elements = number_of_elements;
}
