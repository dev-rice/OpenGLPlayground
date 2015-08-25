#include "Transform3D.hpp"

Transform3D::Transform3D() {
    setPosition(glm::vec3(0, 0, 0));
    setScale(glm::vec3(1, 1, 1));

    setLocalAxes();
}

void Transform3D::setLocalAxes() {
    local_x = glm::vec3(1.0f, 0.0f, 0.0f);
    local_y = glm::vec3(0.0f, 1.0f, 0.0f);
    local_z = glm::vec3(0.0f, 0.0f, 1.0f);
}

void Transform3D::moveByGlobal(glm::vec3 move_vector) {
    setPosition(getPosition() + move_vector);
}

void Transform3D::rotateByGlobal(glm::vec3 rotation_vector) {
    rotateByAxisAngle(glm::vec3(1, 0, 0), rotation_vector.x);
    rotateByAxisAngle(glm::vec3(0, 1, 0), rotation_vector.y);
    rotateByAxisAngle(glm::vec3(0, 0, 1), rotation_vector.z);

    transformLocalAxes(rotation_matrix);
}

void Transform3D::transformLocalAxes(glm::mat4 rotation_matrix) {
    // Transform the camera axes
    glm::vec4 local_x_4 = rotation_matrix * glm::vec4(1.0f, 0.0f, 0.0f, 1.0f);
    glm::vec4 local_y_4 = rotation_matrix * glm::vec4(0.0f, 1.0f, 0.0f, 1.0f);
    glm::vec4 local_z_4 = rotation_matrix * glm::vec4(0.0f, 0.0f, 1.0f, 1.0f);

    local_x = glm::vec3(local_x_4);
    local_y = glm::vec3(local_y_4);
    local_z = glm::vec3(local_z_4);

}

void Transform3D::moveByLocal(glm::vec3 move_vector) {
    moveXLocal(move_vector.x);
    moveYLocal(move_vector.y);
    moveZLocal(move_vector.z);
}

void Transform3D::moveXLocal(float move_amount){
    moveByGlobal(move_amount * local_x);
}

void Transform3D::moveYLocal(float move_amount){
    moveByGlobal(move_amount * local_y);
}

void Transform3D::moveZLocal(float move_amount){
    moveByGlobal(move_amount * local_z);
}

void Transform3D::rotateByLocal(glm::vec3 rotation_vector) {
    rotateByAxisAngle(local_x, rotation_vector.x);
    rotateByAxisAngle(local_y, rotation_vector.y);
    rotateByAxisAngle(local_z, rotation_vector.z);

    transformLocalAxes(getRotationMatrix());
}

void Transform3D::rotateByAxisAngle(glm::vec3 axis, float angle){
    glm::quat quaternion =  glm::angleAxis(angle, axis);
    rotateByMatrix(glm::toMat4(quaternion));
}

void Transform3D::rotateByMatrix(glm::mat4 matrix_to_rotate_by) {
    setRotationMatrix(matrix_to_rotate_by * getRotationMatrix());
}

void Transform3D::setRotationMatrix(glm::mat4 rotation_matrix) {
    this->rotation_matrix = rotation_matrix;
}

glm::mat4 Transform3D::calculateTranslationMatrix() {
    return glm::translate(glm::mat4(), position);
}

glm::mat4 Transform3D::calculateScaleMatrix() {
    return glm::scale(scale);
}

float Transform3D::distanceTo(Transform3D& other_transform_3D) {
    return glm::distance(getPosition(), other_transform_3D.getPosition());
}

glm::mat4 Transform3D::getModelMatrix() {
    return getTranslationMatrix() * getRotationMatrix() * getScaleMatrix();
}

glm::mat4 Transform3D::getInverseModelMatrix() {
    return glm::inverse(getModelMatrix());
}

glm::mat4 Transform3D::getRotationMatrix() {
    return rotation_matrix;
}

glm::mat4 Transform3D::getTranslationMatrix() {
    return calculateTranslationMatrix();
}

glm::mat4 Transform3D::getScaleMatrix() {
    return calculateScaleMatrix();
}

glm::vec3 Transform3D::getPosition() {
    return position;
}

glm::vec3 Transform3D::getScale() {
    return scale;
}

void Transform3D::setPosition(glm::vec3 position) {
    this->position = position;
}

void Transform3D::setScale(glm::vec3 scale) {
    this->scale = scale;
}
