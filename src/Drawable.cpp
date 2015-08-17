#include "Drawable.hpp"

Drawable::Drawable(Mesh& mesh, ShaderProgram& shader) : mesh(&mesh), shader(&shader) {

    mesh.linkToShader(getShaderProgram());

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

ShaderProgram& Drawable::getShaderProgram() {
    return *shader;
}

void Drawable::draw(Camera& camera) {
    getMesh().prepareToBeDrawn();

    getShaderProgram().use();

    glm::mat4 model = glm::translate(glm::mat4(), getPosition());
    GLint model_uniform = getShaderProgram().getUniformLocation( "model");
    glUniformMatrix4fv(model_uniform, 1, GL_FALSE, glm::value_ptr(model));

    glm::mat4 view = camera.getViewMatrix();
    GLint view_uniform = getShaderProgram().getUniformLocation("view");
    glUniformMatrix4fv(view_uniform, 1, GL_FALSE, glm::value_ptr(view));

    glm::mat4 proj = camera.getProjectionMatrix();
    GLint proj_uniform = getShaderProgram().getUniformLocation("proj");
    glUniformMatrix4fv(proj_uniform, 1, GL_FALSE, glm::value_ptr(proj));

    getMesh().draw();
}
