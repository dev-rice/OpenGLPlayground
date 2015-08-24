#include "Mouse.hpp"

Mouse::Mouse() {
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
    SDL_PumpEvents();
    SDL_GetMouseState(&x, &y);
    return glm::vec2(x, y);
}

void Mouse::setPositionInWindow(Window& window, glm::vec2 position){
    SDL_WarpMouseInWindow(window.getSDLWindow(), position.x, position.y);
}

void Mouse::centerInWindow(Window& window){
    setPositionInWindow(window, window.getViewport().getCenter());
}
