#include "Drawable.hpp"

Drawable::Drawable(Mesh& mesh, ShaderProgram& shader, Material& material) : mesh(mesh), shader(shader), material(material) {

    getMaterial().setTextureLocationsInShader(getShaderProgram());
    getMesh().linkToShader(getShaderProgram());
    show();

}

void Drawable::draw(Camera& camera, Transform3D& transform_3D) {
    if (isHidden()){
        return;
    }

    getMesh().prepareToBeDrawn();
    getShaderProgram().use();

    getMaterial().useTextures();

    glm::mat4 model = transform_3D.getModelMatrix();
    GLint model_uniform = getShaderProgram().getUniformLocation("model");
    glUniformMatrix4fv(model_uniform, 1, GL_FALSE, glm::value_ptr(model));

    glm::mat4 view = camera.getViewMatrix();
    GLint view_uniform = getShaderProgram().getUniformLocation("view");
    glUniformMatrix4fv(view_uniform, 1, GL_FALSE, glm::value_ptr(view));

    glm::mat4 proj = camera.getProjectionMatrix();
    GLint proj_uniform = getShaderProgram().getUniformLocation("proj");
    glUniformMatrix4fv(proj_uniform, 1, GL_FALSE, glm::value_ptr(proj));

    // glm::mat4 rotation_matrix(
    //     view[0][0], view[1][0], view[2][0], 0,
    //     view[0][1], view[1][1], view[2][1], 0,
    //     view[0][2], view[1][2], view[2][2], 0,
    //     0         , 0         , 0         , 1
    // );
    //
    // GLint rotation_matrix_uniform = getShaderProgram().getUniformLocation("rotation_matrix");
    // glUniformMatrix4fv(rotation_matrix_uniform, 1, GL_FALSE, glm::value_ptr(rotation_matrix));

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
    return mesh;
}

ShaderProgram& Drawable::getShaderProgram() {
    return shader;
}

Material& Drawable::getMaterial() {
    return material;
}
