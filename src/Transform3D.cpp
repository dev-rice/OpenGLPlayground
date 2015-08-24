#include "Transform3D.hpp"

Transform3D::Transform3D() {
    setPosition(glm::vec3(0, 0, 0));
    setRotationInGlobalCoordinates(glm::vec3(0, 0, 0));
    setScale(glm::vec3(1, 1, 1));
}

glm::vec3 Transform3D::getPosition() {
    return position;
}

glm::vec3 Transform3D::getRotationInGlobalCoordinates() {
    return rotation_in_global_coordinates;
}

glm::vec3 Transform3D::getScale() {
    return scale;
}

void Transform3D::setPosition(glm::vec3 position) {
    this->position = position;
}

void Transform3D::setRotationInGlobalCoordinates(glm::vec3 rotation_in_global_coordinates) {
    this->rotation_in_global_coordinates = rotation_in_global_coordinates;
}

void Transform3D::setScale(glm::vec3 scale) {
    this->scale = scale;
}

void Transform3D::moveByGlobal(glm::vec3 move_vector) {
    setPosition(getPosition() + move_vector);
}

void Transform3D::rotateByGlobal(glm::vec3 rotation_vector) {
    setRotationInGlobalCoordinates(getRotationInGlobalCoordinates() + rotation_vector);
}

void Transform3D::moveByLocal(glm::vec3 move_vector) {

}

void Transform3D::rotateByLocal(glm::vec3 rotation_vec) {

}

glm::mat4 Transform3D::getModelMatrix() {
    return getTranslationMatrix() * getRotationMatrix() * getScaleMatrix();
}

glm::mat4 Transform3D::getRotationMatrix() {
    return calculateRotationMatrix();
}

glm::mat4 Transform3D::getTranslationMatrix() {
    return calculateTranslationMatrix();
}

glm::mat4 Transform3D::getScaleMatrix() {
    return calculateScaleMatrix();
}

glm::mat4 Transform3D::calculateModelMatrix() {
    return calculateTranslationMatrix() * calculateRotationMatrix();
}

glm::mat4 Transform3D::calculateRotationMatrix() {
    // Rotate the model about each axis.
    float cx = cos(getRotationInGlobalCoordinates().x);
    float sx = sin(getRotationInGlobalCoordinates().x);

    float cy = cos(getRotationInGlobalCoordinates().y);
    float sy = sin(getRotationInGlobalCoordinates().y);

    float cz = cos(getRotationInGlobalCoordinates().z);
    float sz = sin(getRotationInGlobalCoordinates().z);



    glm::mat4 rotation_x = glm::mat4( 1, 0 ,  0 , 0,
                                      0, cx, -sx, 0,
                                      0, sx,  cx, 0,
                                      0, 0 ,  0 , 1);

    glm::mat4 rotation_y = glm::mat4(  cy,  0, -sy, 0,
                                       0 ,  1,  0 , 0,
                                       sy,  0,  cy, 0,
                                       0 ,  0,  0 , 1);

    glm::mat4 rotation_z = glm::mat4( cz, -sz, 0, 0,
                                      sz,  cz, 0, 0,
                                      0 ,  0 , 1, 0,
                                      0 ,  0 , 0, 1);

   // The convention followed is rotate around X-axis, then Y-axis, and finally Z-axis.
   glm::mat4 rotation_matrix;
   rotation_matrix = rotation_x * rotation_matrix;
   rotation_matrix = rotation_y * rotation_matrix;
   rotation_matrix = rotation_z * rotation_matrix;

   return rotation_matrix;
}

glm::mat4 Transform3D::calculateTranslationMatrix() {
    return glm::translate(glm::mat4(), position);
}

glm::mat4 Transform3D::calculateScaleMatrix() {
    return glm::scale(scale);
}
