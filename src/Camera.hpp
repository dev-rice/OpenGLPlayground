#ifndef Camera_h
#define Camera_h

#include <iostream>

#include "includes/glm.hpp"

#include "Window.hpp"

using namespace std;

class Camera {
public:
    Camera(Viewport& viewport, float field_of_view, float near_clip, float far_clip);

    void moveByGlobal(glm::vec3 move_vector);
    void moveByLocal(glm::vec3 move_vector);

    void rotateByLocal(glm::vec3 rotation_vector);

    glm::mat4 getViewMatrix();
    glm::mat4 getProjectionMatrix();

    void setPosition(glm::vec3);
    void setRotationInLocalCoordinates(glm::vec3);

    Viewport& getViewport();

    void printEverything();

    void setNearClip(float near_clip);
    void setFarClip(float far_clip);

    float getNearClip();
    float getFarClip();

    float getFieldOfView();
    glm::vec3 getPosition();
    glm::vec3 getRotationInLocalCoordinates();

private:

    void setLocalAxes();
    void setIntrinsicParameters();

    void moveXLocal(float);
    void moveYLocal(float);
    void moveZLocal(float);

    glm::mat4 calculateProjectionMatrix();
    glm::mat4 calculateViewMatrix();

    glm::mat3 calculateRotationMatrix();
    void transformCameraAxes(glm::mat3 rotation_matrix);

    glm::mat4 lookAt(glm::vec3 look_direction);

    glm::vec3 position;
    glm::vec3 rotation_in_local_coordinates;

    glm::vec3 local_x;
    glm::vec3 local_y;
    glm::vec3 local_z;

    // Proj matrix and intrinsic values
    float field_of_view;
    float near_clip;
    float far_clip;
    glm::mat4 proj_matrix;
    glm::mat4 view_matrix;

    Viewport* viewport;
};

#endif
