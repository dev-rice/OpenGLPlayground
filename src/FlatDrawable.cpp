#include "FlatDrawable.hpp"

FlatDrawable::FlatDrawable(Mesh& mesh, ShaderProgram& shader_program) : mesh(&mesh), shader_program(&shader_program) {

    setWidth(1);
    setHeight(1);
    setPositionOfCenter(glm::vec2(0, 0));

    getMesh().linkToShader(getShaderProgram());

}

void FlatDrawable::draw() {
    getMesh().prepareToBeDrawn();
    getShaderProgram().use();

    glm::mat3 transformation = glm::mat3(
                   getWidth() , 0          , getPositionOfCenter().x,
                   0          , getHeight(), getPositionOfCenter().y,
                   0          , 0          , 1);

    GLint transformation_location = getShaderProgram().getUniformLocation("transformation");
    glUniformMatrix3fv(transformation_location, 1, GL_FALSE, glm::value_ptr(transformation));

    getMesh().draw();
}

void FlatDrawable::setWidth(float width) {
    this->width = width;
}

void FlatDrawable::setHeight(float height) {
    this->height = height;
}

void FlatDrawable::setPositionOfCenter(glm::vec2 position_of_center) {
    this->position_of_center = position_of_center;
}

float FlatDrawable::getWidth() {
    return width;
}

float FlatDrawable::getHeight() {
    return height;
}

glm::vec2 FlatDrawable::getPositionOfCenter() {
    return position_of_center;
}

Mesh& FlatDrawable::getMesh() {
    return *mesh;
}
ShaderProgram& FlatDrawable::getShaderProgram() {
    return *shader_program;
}
