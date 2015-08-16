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
