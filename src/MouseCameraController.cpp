#include "MouseCameraController.hpp"

MouseCameraController::MouseCameraController(Mouse& mouse, Transform3D& camera_transform, Window& window, float sensitivity) : mouse(mouse), camera_transform(camera_transform), window(window), sensitivity(sensitivity) {

    mouse.hide();
    resetToBasePosition();

}

void MouseCameraController::update() {

    glm::vec2 change_in_position = getChangeFromLastPosition();
    glm::vec3 rotation_vector = calculateRotationVectorFromChange(change_in_position);

    getCameraTransform().rotateByLocal(glm::vec3(rotation_vector.x, 0, 0));
    getCameraTransform().rotateByGlobal(glm::vec3(0, rotation_vector.y, 0));


    resetToBasePosition();
}

glm::vec3 MouseCameraController::calculateRotationVectorFromChange(glm::vec2 change_in_position) {

    glm::vec3 rotation_vector(-change_in_position.y, -change_in_position.x, 0);
    return rotation_vector * getSensitivity();
}

void MouseCameraController::setLastPosition(glm::vec2 last_position) {
    this->last_position = last_position;
}

glm::vec2 MouseCameraController::getLastPosition() {
    return last_position;
}

glm::vec2 MouseCameraController::getChangeFromLastPosition() {
    return getMouse().getPosition() - getLastPosition();

}

void MouseCameraController::resetToBasePosition() {
    getMouse().centerInWindow(getWindow());
    setLastPosition(getMouse().getPosition());
}


Mouse& MouseCameraController::getMouse() {
    return mouse;
}

Transform3D& MouseCameraController::getCameraTransform() {
    return camera_transform;
}

Window& MouseCameraController::getWindow() {
    return window;
}

float MouseCameraController::getSensitivity() {
    return sensitivity;
}
