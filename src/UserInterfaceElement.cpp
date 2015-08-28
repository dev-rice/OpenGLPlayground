#include "UserInterfaceElement.hpp"

UserInterfaceElement::UserInterfaceElement(Viewport& viewport, FlatDrawable flat_drawable, Transform2D transform_2D) : viewport(viewport), flat_drawable(move(flat_drawable)), transform_2D(move(transform_2D)) {

}

void UserInterfaceElement::draw() {
    getFlatDrawable().draw(getTransform2D());
}

void UserInterfaceElement::setWidthInPixels(int width_in_pixels) {
    float gl_scale_x = (float)width_in_pixels / (float)getViewport().getWidth();

    glm::vec2 current_scale = getTransform2D().getScale();

    getTransform2D().setScale(glm::vec2(gl_scale_x, current_scale.y));
}

void UserInterfaceElement::setHeightInPixels(int height_in_pixels) {
    float gl_scale_y = (float)height_in_pixels / (float)getViewport().getHeight();

    glm::vec2 current_scale = getTransform2D().getScale();

    getTransform2D().setScale(glm::vec2(current_scale.x, gl_scale_y));

}

void UserInterfaceElement::setCenterInPixels(glm::vec2 center_in_pixels) {
    glm::vec2 viewport_dimensions(getViewport().getWidth(), getViewport().getHeight());

    glm::vec2 center_to_viewport_dimensions = center_in_pixels / viewport_dimensions;

    glm::vec2 center_to_viewport_dimensions_times_two = center_to_viewport_dimensions * 2.0f;

    glm::vec2 gl_center(center_to_viewport_dimensions_times_two.x - 1.0, -center_to_viewport_dimensions_times_two.y + 1);

    getTransform2D().setPositionOfCenter(gl_center);
}

Viewport& UserInterfaceElement::getViewport() {
    return viewport;
}

FlatDrawable& UserInterfaceElement::getFlatDrawable() {
    return flat_drawable;
}

Transform2D& UserInterfaceElement::getTransform2D() {
    return transform_2D;
}
