#include "Camera.hpp"

Camera::Camera(Viewport& viewport, glm::vec3 position, glm::vec3 rotation, float fov){

    this->position = position;
    this->rotation = rotation;

    local_x = glm::vec3(1.0f, 0.0f, 0.0f);
    local_y = glm::vec3(0.0f, 1.0f, 0.0f);
    local_z = glm::vec3(0.0f, 0.0f, 1.0f);

    // Default projection matrix
    int width = viewport.getWidth();
    int height = viewport.getHeight();

    // Set intrinsic parameters
    this->fov = fov;
    aspect_ratio = (float)width / (float)height;
    near_clip = 0.1f;
    far_clip = 500.0f;
    updateProjectionMatrix();

}

void Camera::setPosition(glm::vec3 position){
    this->position = position;
}

void Camera::setRotation(glm::vec3 rotation){
    this->rotation = rotation;
}

void Camera::moveX(float move_amount){
    moveByGlobal(move_amount * local_x);
}

void Camera::moveY(float move_amount){
    moveByGlobal(move_amount * local_y);
}

void Camera::moveZ(float move_amount){
    moveByGlobal(move_amount * local_z);
}

void Camera::moveByGlobal(glm::vec3 move_vector) {
    setPosition(getPosition() + move_vector);
}

void Camera::moveByLocal(glm::vec3 move_vector) {
    moveX(move_vector.x);
    moveY(move_vector.y);
    moveZ(move_vector.z);
}

void Camera::moveGlobalX(float move_amount){
    moveByGlobal(glm::vec3(1, 0, 0) * move_amount);
}

void Camera::moveGlobalY(float move_amount){
    moveByGlobal(glm::vec3(0, 1, 0) * move_amount);
}

void Camera::moveGlobalZ(float move_amount){
    moveByGlobal(glm::vec3(0, 0, 1) * move_amount);
}

void Camera::rotateX(float rotate_amount){
    rotation.x += rotate_amount;
}

void Camera::rotateY(float rotate_amount){
    rotation.y += rotate_amount;
}

void Camera::rotateZ(float rotate_amount){
    rotation.z += rotate_amount;
}

glm::mat4 Camera::getViewMatrix(){
    // Original vectors
    // eye      <x, y, z>
    // center   <x, y, z> - <0, 0, 1>
    // up       <0, 1, 0>
    glm::vec3 eye    = position;
    glm::vec3 center = position - glm::vec3(0.0f, 0.0f, 1.0f);
    glm::vec3 up     = local_y;

    float cx = cos(rotation.x);
    float sx = sin(rotation.x);

    float cy = cos(rotation.y);
    float sy = sin(rotation.y);

    glm::mat3 rotation_x = glm::mat3(  1 ,  0 ,  0 ,
                                       0 ,  cx, -sx,
                                       0 ,  sx,  cx  );

    glm::mat3 rotation_y = glm::mat3(  cy,  0 , -sy,
                                       0 ,  1 ,  0 ,
                                       sy,  0 ,  cy  );

    glm::mat3 rotation_matrix = rotation_y * rotation_x;

    // Transform the center vector
    center = position - (rotation_matrix * glm::vec3(0.0f, 0.0f, 1.0f));

    // Transform the camera axes
    local_x = rotation_matrix * glm::vec3(1.0f, 0.0f, 0.0f);
    local_y = rotation_matrix * glm::vec3(0.0f, 1.0f, 0.0f);
    local_z = rotation_matrix * glm::vec3(0.0f, 0.0f, 1.0f);

    view_matrix = glm::lookAt(eye, center, up);

    return view_matrix;
}

glm::mat4 Camera::getProjectionMatrix(){
    return proj_matrix;
}

glm::vec3 Camera::getPosition(){
    return position;
}

glm::vec3 Camera::getRotation(){
    return rotation;
}

float Camera::getFOV(){
    return fov;
}

void Camera::updateProjectionMatrix(){
    // Use all of the intrinsic values to create the projection matrix
    proj_matrix = glm::perspective(fov, aspect_ratio, near_clip, far_clip);
}
