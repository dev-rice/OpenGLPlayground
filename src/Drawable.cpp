#include "Drawable.hpp"

Drawable::Drawable(Mesh& mesh, ShaderProgram& shader, TextureManager& texture_manager) : mesh(&mesh), shader(&shader), texture_manager(&texture_manager) {

    getTextureManager().setTextureLocationsInShader(getShaderProgram());
    getMesh().linkToShader(getShaderProgram());
    show();

}

void Drawable::draw(Camera& camera, Transform3D& transform_3D) {
    if (isHidden()){
        return;
    }

    getMesh().prepareToBeDrawn();
    getShaderProgram().use();

    getTextureManager().useTextures();

    glm::mat4 model = transform_3D.getModelMatrix();
    GLint model_uniform = getShaderProgram().getUniformLocation("model");
    glUniformMatrix4fv(model_uniform, 1, GL_FALSE, glm::value_ptr(model));

    glm::mat4 view = camera.getViewMatrix();
    GLint view_uniform = getShaderProgram().getUniformLocation("view");
    glUniformMatrix4fv(view_uniform, 1, GL_FALSE, glm::value_ptr(view));

    glm::mat4 proj = camera.getProjectionMatrix();
    GLint proj_uniform = getShaderProgram().getUniformLocation("proj");
    glUniformMatrix4fv(proj_uniform, 1, GL_FALSE, glm::value_ptr(proj));

    getMesh().draw();
}

void Drawable::show() {
    is_hidden = false;
}

void Drawable::hide() {
    is_hidden = true;
}

bool Drawable::isHidden() {
    return is_hidden;
}

void Drawable::toggleVisibility() {
    if (isHidden()) {
        show();
    } else {
        hide();
    }
}

Mesh& Drawable::getMesh() {
    return *mesh;
}

ShaderProgram& Drawable::getShaderProgram() {
    return *shader;
}

TextureManager& Drawable::getTextureManager() {
    return *texture_manager;
}
