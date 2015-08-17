#ifndef Mouse_h
#define Mouse_h

#include "includes/sdl.hpp"

#include "window.hpp"

class Mouse {
public:
    Mouse(Window& window);
    void hide();
    void show();
    void toggleVisibility();
    bool isHidden();
    glm::vec2 getPosition();
    void setPosition(glm::vec2 position);
    void centerInWindow();

private:
    void setWindow(Window& window);
    Window& getWindow();

    void setHidden(bool hidden);
    bool is_hidden;

    Window* window;
};

#endif
