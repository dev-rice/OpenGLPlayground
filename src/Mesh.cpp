#include "Mesh.hpp"

Mesh::Mesh(MeshFileParser& mesh_file_parser) : mesh_file_parser(&mesh_file_parser) {

    createVAO();
    createVBO();
    createEBO();

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

void Mesh::createVBO() {
    // Create a Vertex Buffer Object and copy the vertex data to it
    GLuint vbo;
    glGenBuffers(1, &vbo);

    vector<GLfloat> vertices = getVertices();

    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(GLfloat), vertices.data(), GL_STATIC_DRAW);

}

vector<GLfloat> Mesh::getVertices() {
    return getMeshFileParser().getVertexArray();
}

vector<GLuint> Mesh::getElements() {
    return getMeshFileParser().getFaceArray();
}

void Mesh::createEBO() {
    // Create an element array
    GLuint ebo;
    glGenBuffers(1, &ebo);

    vector<GLuint> elements = getElements();

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
    if (!isHidden()) {
        drawAllElements();
    }
}

void Mesh::drawAllElements() {
    glDrawElements(GL_TRIANGLES, getNumElements(), GL_UNSIGNED_INT, 0);
}

int Mesh::getNumElements() {
    return getElements().size();
}

void Mesh::show() {
    is_hidden = false;
}

void Mesh::hide() {
    is_hidden = true;
}

bool Mesh::isHidden() {
    return is_hidden;
}

void Mesh::toggleVisibility() {
    if (isHidden()) {
        show();
    } else {
        hide();
    }
}

MeshFileParser& Mesh::getMeshFileParser() {
    return *mesh_file_parser;
}
