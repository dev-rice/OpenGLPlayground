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
    MouseCameraController(Mouse& mouse, Transform3D& camera_transform, Window& window, float sensitivity);

    void update();

private:
    glm::vec2 getChangeFromLastPosition();
    glm::vec3 calculateRotationVectorFromChange(glm::vec2 change);

    void resetToBasePosition();

    void setLastPosition(glm::vec2 position);
    glm::vec2 getLastPosition();

    Transform3D& getCameraTransform();
    Mouse& getMouse();
    Window& getWindow();
    float getSensitivity();

    Mouse* mouse;
    Transform3D* camera_transform;
    Window* window;

    float sensitivity;
    glm::vec2 last_position;

};

#endif
