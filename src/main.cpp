#include "includes/gl.hpp"
#include "includes/sdl.hpp"
#include "Window.hpp"
#include "OpenGLContext.hpp"
#include "Mouse.hpp"

#include <iostream>
#include <cstdio>

using namespace std;

char getKeyboardInputCharacter(SDL_Event& event) {

    char key = 0;
    if (event.type == SDL_KEYDOWN || event.type == SDL_KEYUP) {
        SDL_Keycode keycode = event.key.keysym.sym;
        key = keycode;
        printf("%c\n", key);
    }

    return key;
}

void handleInputs(Mouse& mouse, Window& window) {
    // Misleading argument and function name combination. The input handling does not draw from the mouse or window at all, it simply does things with them

    SDL_Event event;
    SDL_PollEvent(&event);
    if (event.type == SDL_QUIT) {
        window.requestClose();
    }


    // SDL_Event event;
    // SDL_PollEvent(&event);
    //
    // SDL_Scancode key_scancode = event.key.keysym.scancode;
    char key = getKeyboardInputCharacter(event);
    if (key == 'm'){
        mouse.hide();
    } else if (key == 'c') {
        mouse.centerInWindow();
    }
}

int main(int argc, char* argv[]) {

    Window window(1600, 900, false);
    OpenGLContext gl_context(4, 1, window);
    Mouse mouse(window);

    // Display loop
    while(window.isOpen()) {
        handleInputs(mouse, window);
        window.display();
    }

    // Close the window
    window.close();

    // Add a line break before going back to the terminal prompt.
    printf("\n");

    // Nothing went wrong!
    return 0;
}
