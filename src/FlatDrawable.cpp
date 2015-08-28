#include "FlatDrawable.hpp"

FlatDrawable::FlatDrawable(Mesh& mesh, ShaderProgram& shader_program, Transform2D& transform_2D) : mesh(mesh), shader_program(shader_program), transform_2D(transform_2D) {

    getMesh().linkToShader(getShaderProgram());
    show();

}

void FlatDrawable::draw() {
    if (isHidden()){
        return;
    }

    getMesh().prepareToBeDrawn();
    getShaderProgram().use();

    glm::mat3 transformation = getTransform2D().getTransformationMatrix();
    GLint transformation_location = getShaderProgram().getUniformLocation("transformation");
    glUniformMatrix3fv(transformation_location, 1, GL_FALSE, glm::value_ptr(transformation));

    getMesh().draw();
}

void FlatDrawable::show() {
    is_hidden = false;
}

void FlatDrawable::hide() {
    is_hidden = true;
}

bool FlatDrawable::isHidden() {
    return is_hidden;
}

void FlatDrawable::toggleVisibility() {
    if (isHidden()) {
        show();
    } else {
        hide();
    }
}

Mesh& FlatDrawable::getMesh() {
    return mesh;
}

ShaderProgram& FlatDrawable::getShaderProgram() {
    return shader_program;
}

Transform2D& FlatDrawable::getTransform2D() {
    return transform_2D;
}
