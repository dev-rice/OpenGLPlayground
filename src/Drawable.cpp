#include "Drawable.hpp"

Drawable::Drawable(Mesh& mesh) : mesh(&mesh) {
    setPosition(glm::vec3(0, 0, 0));
}

Mesh& Drawable::getMesh() {
    return *mesh;
}

glm::vec3 Drawable::getPosition() {
    return position;
}

void Drawable::setPosition(glm::vec3 position) {
    this->position = position;
}

void Drawable::draw(Camera& camera) {
    getMesh().prepareToBeDrawn();

    glm::mat4 model = glm::translate(glm::mat4(), getPosition());
    GLint model_uniform = glGetUniformLocation(getMesh().getShaderProgram().getGLId(), "model");
    glUniformMatrix4fv(model_uniform, 1, GL_FALSE, glm::value_ptr(model));

    glm::mat4 view = camera.getViewMatrix();
    GLint view_uniform = glGetUniformLocation(getMesh().getShaderProgram().getGLId(), "view");
    glUniformMatrix4fv(view_uniform, 1, GL_FALSE, glm::value_ptr(view));

    glm::mat4 proj = camera.getProjectionMatrix();
    GLint proj_uniform = glGetUniformLocation(getMesh().getShaderProgram().getGLId(), "proj");
    glUniformMatrix4fv(proj_uniform, 1, GL_FALSE, glm::value_ptr(proj));

    getMesh().draw();
}
