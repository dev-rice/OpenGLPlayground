#ifndef MouseCameraController_h
#define MouseCameraController_h

#include <iostream>

#include "includes/glm.hpp"

#include "Mouse.hpp"
#include "Camera.hpp"
#include "Window.hpp"

using namespace std;

class MouseCameraController {
public:
    MouseCameraController(Mouse& mouse, Transform3D& camera_transform, Window& window, float movement_sensitivity, float rotation_sensitivity);

    void update();

private:
    glm::vec3 getMovementVector();
    glm::vec3 getRotationVector();
    glm::vec2 getChangeFromLastPosition();
    glm::vec3 calculateRotationVectorFromChange(glm::vec2 change);

    void resetToBasePosition();

    void setLastPosition(glm::vec2 position);
    glm::vec2 getLastPosition();

    Transform3D& getCameraTransform();
    Mouse& getMouse();
    Window& getWindow();
    float getRotationSensitivity();
    float getMovementSensitivity();

    Mouse& mouse;
    Transform3D& camera_transform;
    Window& window;

    float movement_sensitivity;
    float rotation_sensitivity;
    glm::vec2 last_position;

};

#endif
