#include "FlatDrawable.hpp"

FlatDrawable::FlatDrawable(Mesh& mesh, ShaderProgram& shader_program, Transform2D& transform_2D) : mesh(&mesh), shader_program(&shader_program), transform_2D(&transform_2D) {

    getMesh().linkToShader(getShaderProgram());

}

void FlatDrawable::draw() {
    getMesh().prepareToBeDrawn();
    getShaderProgram().use();

    glm::mat3 transformation = getTransform2D().getTransformationMatrix();
    GLint transformation_location = getShaderProgram().getUniformLocation("transformation");
    glUniformMatrix3fv(transformation_location, 1, GL_FALSE, glm::value_ptr(transformation));

    getMesh().draw();
}

Mesh& FlatDrawable::getMesh() {
    return *mesh;
}

ShaderProgram& FlatDrawable::getShaderProgram() {
    return *shader_program;
}

Transform2D& FlatDrawable::getTransform2D() {
    return *transform_2D;
}
