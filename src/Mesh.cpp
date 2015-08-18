#include "Mesh.hpp"

Mesh::Mesh(MeshLoader& mesh_loader) : mesh_loader(&mesh_loader) {

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
    // return {
    //      0.5f,  0.5f,  0.5f, 0.0f, 0.0f, 1.0f,
    //     -0.5f,  0.5f,  0.5f, 0.0f, 0.0f, 1.0f,
    //     -0.5f, -0.5f,  0.5f, 0.0f, 0.0f, 1.0f,
    //      0.5f, -0.5f,  0.5f, 0.0f, 0.0f, 1.0f,
    //
    //      0.5f,  0.5f, -0.5f, 0.0f, 1.0f, 0.0f,
    //     -0.5f,  0.5f, -0.5f, 0.0f, 1.0f, 0.0f,
    //     -0.5f,  0.5f,  0.5f, 0.0f, 1.0f, 0.0f,
    //      0.5f,  0.5f,  0.5f, 0.0f, 1.0f, 0.0f,
    //
    //     -0.5f,  0.5f,  0.5f, 0.0f, 1.0f, 1.0f,
    //     -0.5f,  0.5f, -0.5f, 0.0f, 1.0f, 1.0f,
    //     -0.5f, -0.5f, -0.5f, 0.0f, 1.0f, 1.0f,
    //     -0.5f, -0.5f,  0.5f, 0.0f, 1.0f, 1.0f,
    //
    // };

    return getMeshLoader().getVertexArray();
}

vector<GLuint> Mesh::getElements() {
    //  return {
    //     0, 1, 2,
    //     2, 3, 0,
    //
    //     4, 5, 6,
    //     6, 7, 4,
    //
    //     8, 9, 10,
    //     10, 11, 8,
    //
    // };

    return getMeshLoader().getFaceArray();

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
    GLint posAttrib = glGetAttribLocation(shaderProgram.getGLId(), "position");
    glEnableVertexAttribArray(posAttrib);
    glVertexAttribPointer(posAttrib, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), 0);

    GLint colAttrib = glGetAttribLocation(shaderProgram.getGLId(), "color");
    glEnableVertexAttribArray(colAttrib);
    glVertexAttribPointer(colAttrib, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (void*)(3 * sizeof(GLfloat)));
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

MeshLoader& Mesh::getMeshLoader() {
    return *mesh_loader;
}
