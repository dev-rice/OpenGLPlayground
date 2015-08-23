#include "Transform2D.hpp"

Transform2D::Transform2D() {
    setScale(glm::vec2(1, 1));
    setPositionOfCenter(glm::vec2(0, 0));
}

glm::mat3 Transform2D::getTransformationMatrix() {
    return calculateTransformationMatrix();
}

glm::mat3 Transform2D::calculateTransformationMatrix() {
    return getScaleMatrix() *  getTranslationMatrix();
}

glm::mat3 Transform2D::getTranslationMatrix() {
    return calculateTranslationMatrix();
}

glm::mat3 Transform2D::getScaleMatrix() {
    return calculateScaleMatrix();
}

glm::mat3 Transform2D::calculateTranslationMatrix() {
    return glm::mat3(
        1, 0, getPositionOfCenter().x,
        0, 1, getPositionOfCenter().y,
        0, 0, 1
    );
}

glm::mat3 Transform2D::calculateScaleMatrix() {
    return glm::mat3(
        getScale().x, 0           , 0,
        0           , getScale().y, 0,
        0           , 0           , 1
    );
}

void Transform2D::setScale(glm::vec2 scale) {
    this->scale = scale;
}

void Transform2D::setPositionOfCenter(glm::vec2 position_of_center) {
    this->position_of_center = position_of_center;
}

glm::vec2 Transform2D::getScale() {
    return scale;
}

glm::vec2 Transform2D::getPositionOfCenter() {
    return position_of_center;
}
