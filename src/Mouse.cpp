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

glm::vec2 Mouse::getPosition() {
    int x, y;
    SDL_GetMouseState(&x, &y);
    return glm::vec2(x, y);
}

void Mouse::setPosition(glm::vec2 position){
    SDL_WarpMouseInWindow(getWindow().getSDLWindow(), position.x, position.y);
}

void Mouse::centerInWindow(){
    setPosition(getWindow().getViewport().getCenter());
}
