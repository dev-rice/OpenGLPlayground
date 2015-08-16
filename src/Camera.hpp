#ifndef Camera_h
#define Camera_h

#include "includes/glm.hpp"

#include "Window.hpp"

class Camera {
public:
    Camera(Viewport& viewport, glm::vec3, glm::vec3, float);

    void moveX(float);
    void moveY(float);
    void moveZ(float);

    void rotateX(float);
    void rotateY(float);
    void rotateZ(float);

    void moveGlobalX(float);
    void moveGlobalY(float);
    void moveGlobalZ(float);

    void setPosition(glm::vec3);
    void setRotation(glm::vec3);

    void print();

    glm::vec3 getPosition();
    glm::vec3 getRotation();
    glm::mat4 getViewMatrix();
    glm::mat4 getProjectionMatrix();
    float getFOV();

private:
    void initializer(glm::vec3, glm::vec3, float, float, float);
    void updateProjectionMatrix();

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
