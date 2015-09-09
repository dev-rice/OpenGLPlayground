#include "Mesh.hpp"

Mesh::Mesh(MeshData& mesh_data, VertexSpecification& vertex_specification) : vertex_specification(vertex_specification) {
    sendMeshDataToOpenGL(mesh_data);
    setMeshStatsFromMeshData(mesh_data);
}

void Mesh::sendMeshDataToOpenGL(MeshData& mesh_data) {
    createVAO();
    createVBO(mesh_data.getVertices());
    createEBO(mesh_data.getElements());
}

void Mesh::setMeshStatsFromMeshData(MeshData& mesh_data) {
    setNumberOfElements(mesh_data.getElements().size());
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

void Mesh::bindVBO() {
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
}

void Mesh::createVBO(vector<GLfloat>& vertices) {
    glGenBuffers(1, &vbo);
    bindVBO();

    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(GLfloat), vertices.data(), GL_STATIC_DRAW);

}

void Mesh::createEBO(vector<GLuint>& elements) {
    // Create an element array
    glGenBuffers(1, &ebo);

    // Create Element Buffer Object
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, elements.size() * sizeof(GLuint), elements.data(), GL_STATIC_DRAW);
}

void Mesh::linkToShader(ShaderProgram& shader_program) {
    bindVAO();
    bindVBO();
    getVertexSpecification().attachToShader(shader_program);
}

VertexSpecification& Mesh::getVertexSpecification() {
    return vertex_specification;
}

void Mesh::draw() {
    drawAllElementsSolid();
}

void Mesh::drawAllElementsWireframe() {
    drawAllElements(GL_LINES);
}

void Mesh::drawAllElementsSolid() {
    drawAllElements(GL_TRIANGLES);
}

void Mesh::drawAllElements(GLint draw_mode) {
    glDrawElements(draw_mode, getNumberOfElements(), GL_UNSIGNED_INT, 0);
}

int Mesh::getNumberOfTriangles() {
    return getNumberOfElements() / 3;
}

int Mesh::getNumberOfElements() {
    return number_of_elements;
}

void Mesh::setNumberOfElements(int number_of_elements) {
    this->number_of_elements = number_of_elements;
}
