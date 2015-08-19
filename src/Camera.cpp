#include "Camera.hpp"

Camera::Camera(Viewport& viewport, float field_of_view) : field_of_view(field_of_view), viewport(&viewport){

    setLocalAxes();
    setIntrinsicParameters();

}

void Camera::setLocalAxes() {
    local_x = glm::vec3(1.0f, 0.0f, 0.0f);
    local_y = glm::vec3(0.0f, 1.0f, 0.0f);
    local_z = glm::vec3(0.0f, 0.0f, 1.0f);
}

void Camera::setIntrinsicParameters() {
    aspect_ratio = getViewport().getAspectRatio();
    near_clip = 0.1f;
    far_clip = 500.0f;
}

void Camera::setPosition(glm::vec3 position){
    this->position = position;
}

void Camera::setRotationInLocalCoordinates(glm::vec3 rotation_in_local_coordinates){
    this->rotation_in_local_coordinates = rotation_in_local_coordinates;
}

Viewport& Camera::getViewport() {
    return *viewport;
}

void Camera::moveXLocal(float move_amount){
    moveByGlobal(move_amount * local_x);
}

void Camera::moveYLocal(float move_amount){
    moveByGlobal(move_amount * local_y);
}

void Camera::moveZLocal(float move_amount){
    moveByGlobal(move_amount * local_z);
}

void Camera::moveByGlobal(glm::vec3 move_vector) {
    setPosition(getPosition() + move_vector);
}

void Camera::moveByLocal(glm::vec3 move_vector) {
    moveXLocal(move_vector.x);
    moveYLocal(move_vector.y);
    moveZLocal(move_vector.z);
}

void Camera::rotateByLocal(glm::vec3 rotation_vector) {
    setRotationInLocalCoordinates(getRotationInLocalCoordinates() + rotation_vector);
}

glm::mat4 Camera::getViewMatrix(){
    return calculateViewMatrix();
}

glm::mat4 Camera::getProjectionMatrix(){
    return calculateProjectionMatrix();
}

glm::vec3 Camera::getPosition(){
    return position;
}

glm::vec3 Camera::getRotationInLocalCoordinates(){
    return rotation_in_local_coordinates;
}

float Camera::getFOV(){
    return field_of_view;
}

glm::mat4 Camera::calculateViewMatrix() {

    glm::mat3 rotation_matrix = calculateRotationMatrix();

    glm::vec3 look_direction = rotation_matrix * glm::vec3(0.0f, 0.0f, 1.0f);

    transformCameraAxes(rotation_matrix);

    return lookAt(look_direction);

}

glm::mat4 Camera::lookAt(glm::vec3 look_direction) {
    glm::vec3 eye = position;
    glm::vec3 up = local_y;

    return glm::lookAt(eye, eye - look_direction, up);
}

glm::mat3 Camera::calculateRotationMatrix() {
    float cx = cos(getRotationInLocalCoordinates().x);
    float sx = sin(getRotationInLocalCoordinates().x);

    float cy = cos(getRotationInLocalCoordinates().y);
    float sy = sin(getRotationInLocalCoordinates().y);

    glm::mat3 rotation_x = glm::mat3(  1 ,  0 ,  0 ,
                                       0 ,  cx, -sx,
                                       0 ,  sx,  cx  );

    glm::mat3 rotation_y = glm::mat3(  cy,  0 , -sy,
                                       0 ,  1 ,  0 ,
                                       sy,  0 ,  cy  );

    return rotation_y * rotation_x;

}

void Camera::transformCameraAxes(glm::mat3 rotation_matrix) {
    // Transform the camera axes
    local_x = rotation_matrix * glm::vec3(1.0f, 0.0f, 0.0f);
    local_y = rotation_matrix * glm::vec3(0.0f, 1.0f, 0.0f);
    local_z = rotation_matrix * glm::vec3(0.0f, 0.0f, 1.0f);
}

glm::mat4 Camera::calculateProjectionMatrix(){
    // Use all of the intrinsic values to create the projection matrix
    return glm::perspective(field_of_view, aspect_ratio, near_clip, far_clip);
}
