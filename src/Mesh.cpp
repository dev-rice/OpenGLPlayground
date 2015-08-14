#include "Mesh.hpp"

Mesh::Mesh(ShaderProgram& shader) : shader(&shader) {

    // Create a Vertex Array Object
    GLuint vao;
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);

    // Create a Vertex Buffer Object and copy the vertex data to it
    GLuint vbo;
    glGenBuffers(1, &vbo);

    GLfloat vertices[] = {
        -0.5f,  0.5f, 1.0f, 0.0f, 0.0f, // Top-left
         0.5f,  0.5f, 0.0f, 1.0f, 0.0f, // Top-right
         0.5f, -0.5f, 0.0f, 0.0f, 1.0f, // Bottom-right
        -0.5f, -0.5f, 1.0f, 1.0f, 1.0f  // Bottom-left
    };

    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    // Create an element array
    GLuint ebo;
    glGenBuffers(1, &ebo);

    GLuint elements[] = {
        0, 1, 2,
        2, 3, 0
    };

    // Create Element Buffer Object
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(elements), elements, GL_STATIC_DRAW);

    linkMeshToShader(getShaderProgram());

}

ShaderProgram& Mesh::getShaderProgram() {
    return *shader;
}

void Mesh::linkMeshToShader(ShaderProgram& shaderProgram) {
    // Specify the layout of the vertex data
    GLint posAttrib = glGetAttribLocation(shaderProgram.getGLId(), "position");
    glEnableVertexAttribArray(posAttrib);
    glVertexAttribPointer(posAttrib, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), 0);

    GLint colAttrib = glGetAttribLocation(shaderProgram.getGLId(), "color");
    glEnableVertexAttribArray(colAttrib);
    glVertexAttribPointer(colAttrib, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (void*)(2 * sizeof(GLfloat)));
}

void Mesh::clearBuffer() {
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
}

void Mesh::draw() {
    clearBuffer();

    getShaderProgram().use();

    if (!isHidden()) {
        // Draw a rectangle from the 2 triangles using 6 indices
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
    }
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
