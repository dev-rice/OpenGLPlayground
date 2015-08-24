#ifndef Camera_h
#define Camera_h

#include <iostream>

#include "includes/glm.hpp"

#include "Viewport.hpp"
#include "Transform3D.hpp"

using namespace std;

class Camera {
public:
    Camera(Viewport& viewport, Transform3D& transform_3D, float field_of_view, float near_clip, float far_clip);

    void moveByGlobal(glm::vec3 move_vector);
    void moveByLocal(glm::vec3 move_vector);
    void rotateByLocal(glm::vec3 rotation_vector);

    glm::mat4 getViewMatrix();
    glm::mat4 getProjectionMatrix();

    Viewport& getViewport();
    Transform3D& getTransform3D();

    void setNearClip(float near_clip);
    void setFarClip(float far_clip);
    void setFieldOfView(float field_of_view);

    float getNearClip();
    float getFarClip();
    float getFieldOfView();

private:
    void setIntrinsicParameters();

    glm::mat4 calculateProjectionMatrix();
    glm::mat4 calculateViewMatrix();

    glm::mat4 lookAt(glm::vec3 look_direction);

    Viewport* viewport;
    Transform3D* transform_3D;
    float field_of_view;
    float near_clip;
    float far_clip;

};

#endif
