#ifndef Transform3D_h
#define Transform3D_h

#include <memory>

#include "includes/glm.hpp"

using namespace std;

class Transform3D {
public:

    Transform3D();

    virtual void moveByGlobal(glm::vec3 move_vector);
    virtual void rotateByGlobal(glm::vec3 rotation_vec);

    virtual void moveByLocal(glm::vec3 move_vector);
    virtual void rotateByLocal(glm::vec3 rotation_vec);

    virtual void setRelativePosition(glm::vec3 position);
    virtual void setScale(glm::vec3 scale);

    virtual glm::mat4 getModelMatrix();
    virtual glm::mat4 getInverseModelMatrix();

    virtual glm::vec3 getAbsolutePosition();
    virtual glm::vec3 getRelativePosition();
    virtual glm::vec3 getScale();

    virtual Transform3D& getParent();

    // Valid for all subclasses
    float distanceTo(Transform3D& other_transform_3D);

    void setParent(Transform3D& parent);


private:

    bool isOwnParent();
    void setLocalAxes();
    void transformLocalAxes(glm::mat4 rotation_matrix);

    void rotateByAxisAngle(glm::vec3 axis, float angle);

    void moveXLocal(float);
    void moveYLocal(float);
    void moveZLocal(float);

    void setRotationMatrix(glm::mat4 rotation_matrix);
    void rotateByMatrix(glm::mat4 rotation_matrix);

    glm::mat4 getRotationMatrix();
    glm::mat4 getTranslationMatrix();
    glm::mat4 getScaleMatrix();

    glm::mat4 calculateRotationMatrix();
    glm::mat4 calculateTranslationMatrix();
    glm::mat4 calculateScaleMatrix();

    glm::vec3 local_x;
    glm::vec3 local_y;
    glm::vec3 local_z;

    glm::vec3 position;
    glm::vec3 scale;

    glm::mat4 rotation_matrix;

    Transform3D* parent;

};

#endif
