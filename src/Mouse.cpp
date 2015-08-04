#include "Mouse.hpp"

Mouse::Mouse(Window& window) {
    setWindow(window);
    centerInWindow();
    show();
}

bool Mouse::isHidden() {
    return is_hidden;
}

void Mouse::setHidden(bool hidden) {
    is_hidden = hidden;
    if (hidden) {
        SDL_ShowCursor(SDL_DISABLE);
    } else {
        SDL_ShowCursor(SDL_ENABLE);
    }
}

Window& Mouse::getWindow() {
    return *window;
}

void Mouse::setWindow(Window& window) {
    this->window = &window;
}

void Mouse::hide() {
    setHidden(true);
}

void Mouse::show() {
    setHidden(false);
}

void Mouse::toggleVisibility() {
    if (isHidden()) {
        show();
    } else {
        hide();
    }
}

void Mouse::setMousePosition(int x, int y){
    SDL_WarpMouseInWindow(getWindow().getSDLWindow(), x, y);
}

void Mouse::centerInWindow(){
    setMousePosition(getWindow().getWidth() / 2, getWindow().getHeight() / 2);
}
