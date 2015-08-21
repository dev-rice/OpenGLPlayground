#include "Mesh.hpp"

Mesh::Mesh(string filename, MeshFileParser& mesh_file_parser) :  position("position", 3, 0), normal("normal", 3, 3), texture_coordinates("texture_coordinates", 2, 6) {

    mesh_file_parser.loadMeshFromFile(filename);

    setMeshStatsFromParser(mesh_file_parser);
    sendMeshDataToOpenGL(mesh_file_parser);

    mesh_file_parser.clearMeshData();
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
    position.attachToShader(shader_program, getVertexWidth());
    normal.attachToShader(shader_program, getVertexWidth());
    texture_coordinates.attachToShader(shader_program, getVertexWidth());
}

int Mesh::getVertexWidth() {
    return 8;
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
