#ifndef Transform2D_h
#define Transform2D_h

#include "includes/glm.hpp"

class Transform2D {
public:

    Transform2D();

    void setScale(glm::vec2 scale);
    void setPositionOfCenter(glm::vec2 position_of_center);

    glm::vec2 getScale();
    glm::vec2 getPositionOfCenter();

    glm::mat3 getTransformationMatrix();
    glm::mat3 getTranslationMatrix();
    glm::mat3 getScaleMatrix();


private:

    glm::mat3 calculateTransformationMatrix();
    glm::mat3 calculateTranslationMatrix();
    glm::mat3 calculateScaleMatrix();

    glm::vec2 position_of_center;
    glm::vec2 scale;

};

#endif
