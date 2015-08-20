#include "Mesh.hpp"

Mesh::Mesh(string filename, MeshFileParser& mesh_file_parser) {

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
    setNumberOfFaces(mesh_file_parser.getNumberOfFaces());
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
    // Create a Vertex Buffer Object and copy the vertex data to it
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

void Mesh::linkToShader(ShaderProgram& shaderProgram) {
    // Specify the layout of the vertex data
    GLint position_attribute = shaderProgram.getAttributeLocation("position");
    glEnableVertexAttribArray(position_attribute);
    glVertexAttribPointer(position_attribute, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), 0);

    GLint normal_attribute = shaderProgram.getAttributeLocation("normal");
    glEnableVertexAttribArray(normal_attribute);
    glVertexAttribPointer(normal_attribute, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (void*)(3 * sizeof(GLfloat)));

    GLint texture_attribute = shaderProgram.getAttributeLocation("texture_coordinate");
    glEnableVertexAttribArray(texture_attribute);
    glVertexAttribPointer(texture_attribute, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (void*)(6 * sizeof(GLfloat)));
}

void Mesh::draw() {
    drawAllElements();
}

void Mesh::drawAllElements() {
    glDrawElements(GL_TRIANGLES, getNumberOfFaces(), GL_UNSIGNED_INT, 0);
}

int Mesh::getNumberOfFaces() {
    return number_of_faces;
}

void Mesh::setNumberOfFaces(int number_of_faces) {
    this->number_of_faces = number_of_faces;
}
