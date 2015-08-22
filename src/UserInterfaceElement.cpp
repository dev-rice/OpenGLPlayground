#include "UserInterfaceElement.hpp"

UserInterfaceElement::UserInterfaceElement(Viewport& viewport, FlatDrawable& flat_drawable) : viewport(&viewport), flat_drawable(&flat_drawable) {



}

void UserInterfaceElement::draw() {
    getFlatDrawable().draw();
}

void UserInterfaceElement::setWidthInPixels(int width_in_pixels) {
    float width_to_viewport_width = (float)width_in_pixels / (float)getViewport().getWidth();

    float gl_width = width_to_viewport_width * 2.0;

    getFlatDrawable().setWidth(gl_width);
}

void UserInterfaceElement::setHeightInPixels(int height_in_pixels) {
    float height_to_viewport_height = (float)height_in_pixels / (float)getViewport().getHeight();

    float gl_height = height_to_viewport_height * 2.0;

    getFlatDrawable().setHeight(gl_height);

}

void UserInterfaceElement::setCenterInPixels(glm::vec2 center_in_pixels) {
    glm::vec2 viewport_dimensions(getViewport().getWidth(), getViewport().getHeight());

    glm::vec2 center_to_viewport_dimensions = center_in_pixels / viewport_dimensions;

    glm::vec2 center_to_viewport_dimensions_times_two = center_to_viewport_dimensions * 2.0f;

    glm::vec2 gl_center(center_to_viewport_dimensions_times_two.x - 1.0, -center_to_viewport_dimensions_times_two.y + 1);
    getFlatDrawable().setPositionOfCenter(gl_center);
}

Viewport& UserInterfaceElement::getViewport() {
    return *viewport;
}

FlatDrawable& UserInterfaceElement::getFlatDrawable() {
    return *flat_drawable;
}
