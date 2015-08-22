#include "Mesh.hpp"

Mesh::Mesh(MeshData& mesh_data, VertexSpecification& vertex_specification) : vertex_specification(&vertex_specification) {
    sendMeshDataToOpenGL(mesh_data);
    setNumberOfElements(mesh_data.getElements().size());
}

void Mesh::sendMeshDataToOpenGL(MeshData& mesh_data) {
    createVAO();
    createVBO(mesh_data.getVertices());
    createEBO(mesh_data.getElements());
}

void Mesh::sendMeshDataToOpenGL(MeshFileParser& mesh_file_parser) {
    createVAO();
    createVBO(mesh_file_parser.getVertexArray());
    createEBO(mesh_file_parser.getFaceArray());
}

void Mesh::setMeshStatsFromParser(MeshFileParser& mesh_file_parser) {
    setNumberOfElements(mesh_file_parser.getNumberOfElements());
}

void Mesh::createVAO() {
    glGenVertexArrays(1, &vao);
    bindVAO();
}

void Mesh::prepareToBeDrawn() {
    bindVAO();
}

void Mesh::bindVAO() {
    glBindVertexArray(vao);
}

void Mesh::createVBO(vector<GLfloat>& vertices) {
    GLuint vbo;
    glGenBuffers(1, &vbo);

    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(GLfloat), vertices.data(), GL_STATIC_DRAW);

}

void Mesh::createEBO(vector<GLuint>& elements) {
    // Create an element array
    GLuint ebo;
    glGenBuffers(1, &ebo);

    // Create Element Buffer Object
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, elements.size() * sizeof(GLuint), elements.data(), GL_STATIC_DRAW);
}

void Mesh::linkToShader(ShaderProgram& shader_program) {
    getVertexSpecification().attachToShader(shader_program);
}

VertexSpecification& Mesh::getVertexSpecification() {
    return *vertex_specification;
}

void Mesh::draw() {
    drawAllElements();
}

void Mesh::drawAllElements() {
    glDrawElements(GL_TRIANGLES, getNumberOfElements(), GL_UNSIGNED_INT, 0);
}

int Mesh::getNumberOfTriangles() {
    return number_of_elements / 3;
}

int Mesh::getNumberOfElements() {
    return number_of_elements;
}

void Mesh::setNumberOfElements(int number_of_elements) {
    this->number_of_elements = number_of_elements;
}
