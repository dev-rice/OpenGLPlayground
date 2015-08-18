#ifndef Camera_h
#define Camera_h

#include "includes/glm.hpp"

#include "Window.hpp"

class Camera {
public:
    Camera(Viewport& viewport, glm::vec3, glm::vec3, float);

    void moveByGlobal(glm::vec3 move_vector);
    void moveByLocal(glm::vec3 move_vector);

    void rotateByLocal(glm::vec3 rotation_vector);

    glm::mat4 getViewMatrix();
    glm::mat4 getProjectionMatrix();

    void setPosition(glm::vec3);
    void setRotation(glm::vec3);

    float getFOV();
    glm::vec3 getPosition();
    glm::vec3 getRotation();

private:

    void moveXLocal(float);
    void moveYLocal(float);
    void moveZLocal(float);

    void initializer(glm::vec3, glm::vec3, float, float, float);
    glm::mat4 calculateProjectionMatrix();
    glm::mat4 calculateViewMatrix();

    glm::vec3 position;
    glm::vec3 rotation;

    glm::vec3 local_x;
    glm::vec3 local_y;
    glm::vec3 local_z;

    // Proj matrix and intrinsic values
    float fov;
    float aspect_ratio;
    float near_clip;
    float far_clip;
    glm::mat4 proj_matrix;
    glm::mat4 view_matrix;
};

#endif
