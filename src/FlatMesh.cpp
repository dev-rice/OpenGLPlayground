#include "FlatMesh.hpp"

FlatMesh::FlatMesh() : position("position", 2, 0), texture_coordinates("texture_coordinates", 2, 2) {

    std::vector<GLfloat> vertices = {
             -1.0f,  1.0f,  0.0f, 1.0f,
             -1.0f, -1.0f,  0.0f, 0.0f,
              1.0f,  1.0f,  1.0f, 1.0f,
              1.0f, -1.0f,  1.0f, 0.0f,

    };

    std::vector<GLuint> elements = {
            0, 1, 2,
            1, 3, 2,
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

void FlatMesh::linkToShader(ShaderProgram& shader){
    position.attachToShader(shader, getVertexWidth());
    texture_coordinates.attachToShader(shader, getVertexWidth());
}

int FlatMesh::getVertexWidth() {
    return 4;
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

int FlatMesh::getNumberOfTriangles() {
    return number_of_elements / 3;
}

int FlatMesh::getNumberOfElements() {
    return number_of_elements;
}

void FlatMesh::setNumberOfElements(int number_of_elements) {
    this->number_of_elements = number_of_elements;
}
