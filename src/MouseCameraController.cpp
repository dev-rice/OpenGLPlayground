#include "MouseCameraController.hpp"

MouseCameraController::MouseCameraController(Mouse& mouse, Camera& camera, Window& window) : mouse(&mouse), camera(&camera), window(&window) {

    mouse.hide();
    resetToBasePosition();


}

void MouseCameraController::update() {

    glm::vec2 change_in_position = getChangeFromLastPosition();
    change_in_position = change_in_position * 0.001f;

    glm::vec3 rotation_vector = calculateRotationVectorFromChange(change_in_position);
    getCamera().rotateByLocal(rotation_vector);

    resetToBasePosition();
}

glm::vec3 MouseCameraController::calculateRotationVectorFromChange(glm::vec2 change_in_position) {

    return glm::vec3(change_in_position.y, -change_in_position.x, 0);
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
    return *mouse;
}

Camera& MouseCameraController::getCamera() {
    return *camera;
}

Window& MouseCameraController::getWindow() {
    return *window;
}
