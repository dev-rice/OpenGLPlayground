#include "Viewport.hpp"

Viewport::Viewport(int w, int h) {
    width = w;
    height = h;
}

int Viewport::getWidth() {
    return width;
}

int Viewport::getHeight() {
    return height;
}

glm::vec2 Viewport::getCenter() {
    return glm::vec2(width / 2.0f, height / 2.0f);
}
