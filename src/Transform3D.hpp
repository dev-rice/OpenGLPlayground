#ifndef Transform3D_h
#define Transform3D_h

#include "includes/glm.hpp"

class Transform3D {
public:

    Transform3D();

    void moveByGlobal(glm::vec3 move_vector);
    void rotateByGlobal(glm::vec3 rotation_vec);

    void setPosition(glm::vec3 position);
    void setRotationInGlobalCoordinates(glm::vec3 rotation_in_global_coordinates);
    void setScale(glm::vec3 scale);

    glm::vec3 getPosition();
    glm::vec3 getRotationInGlobalCoordinates();
    glm::vec3 getScale();

    glm::mat4 getModelMatrix();

private:
    glm::mat4 getRotationMatrix();
    glm::mat4 getTranslationMatrix();
    glm::mat4 getScaleMatrix();

    glm::mat4 calculateModelMatrix();
    glm::mat4 calculateRotationMatrix();
    glm::mat4 calculateTranslationMatrix();
    glm::mat4 calculateScaleMatrix();

    glm::vec3 position;
    glm::vec3 rotation_in_global_coordinates;
    glm::vec3 scale;

};

#endif
