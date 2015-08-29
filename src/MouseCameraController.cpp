#include "MouseCameraController.hpp"

MouseCameraController::MouseCameraController(Mouse& mouse, Transform3D& camera_transform, Window& window, float movement_sensitivity, float rotation_sensitivity) : mouse(mouse), camera_transform(camera_transform), window(window), movement_sensitivity(movement_sensitivity), rotation_sensitivity(rotation_sensitivity) {

    mouse.hide();
    resetToBasePosition();

}

void MouseCameraController::update() {

    glm::vec3 camera_movement = getMovementVector();
    getCameraTransform().moveByLocal(camera_movement);

    glm::vec3 rotation_vector = getRotationVector();
    getCameraTransform().rotateByLocal(glm::vec3(rotation_vector.x, 0, 0));
    getCameraTransform().rotateByGlobal(glm::vec3(0, rotation_vector.y, 0));

    resetToBasePosition();
}

glm::vec3 MouseCameraController::getMovementVector() {
    // Continuous input
    const Uint8* keyboard = SDL_GetKeyboardState(NULL);

    glm::vec3 camera_movement(0, 0, 0);
    if (keyboard[SDL_SCANCODE_W]) {
        camera_movement += glm::vec3(0, 0, -1);
    }
    if (keyboard[SDL_SCANCODE_S]) {
        camera_movement += glm::vec3(0, 0, 1);
    }
    if (keyboard[SDL_SCANCODE_A]) {
        camera_movement += glm::vec3(-1, 0, 0);
    }
    if (keyboard[SDL_SCANCODE_D]) {
        camera_movement += glm::vec3(1, 0, 0);
    }
    if (keyboard[SDL_SCANCODE_SPACE]) {
        camera_movement += glm::vec3(0, 1, 0);
    }
    if (keyboard[SDL_SCANCODE_LSHIFT]) {
        camera_movement += glm::vec3(0, -1, 0);
    }

    if (glm::length(camera_movement) != 0){
        camera_movement = glm::normalize(camera_movement);
    }
    camera_movement = camera_movement * getMovementSensitivity();

    return camera_movement;
}

glm::vec3 MouseCameraController::getRotationVector() {
    glm::vec2 change_in_position = getChangeFromLastPosition();
    return calculateRotationVectorFromChange(change_in_position);

}

glm::vec3 MouseCameraController::calculateRotationVectorFromChange(glm::vec2 change_in_position) {

    glm::vec3 rotation_vector(-change_in_position.y, -change_in_position.x, 0);
    return rotation_vector * getRotationSensitivity();
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

float MouseCameraController::getMovementSensitivity() {
    return movement_sensitivity;
}

float MouseCameraController::getRotationSensitivity() {
    return rotation_sensitivity;
}
