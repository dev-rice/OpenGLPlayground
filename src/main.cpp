#include "includes/gl.hpp"
#include "includes/sdl.hpp"
#include "Window.hpp"
#include "OpenGLContext.hpp"
#include "Mouse.hpp"
#include "Mesh.hpp"

#include <iostream>
#include <cstdio>

using namespace std;

char getKeyboardInputCharacter(SDL_Event& event) {

    char key = 0;
    if (event.type == SDL_KEYDOWN) {
        SDL_Keycode keycode = event.key.keysym.sym;
        key = keycode;
        printf("%c\n", key);
    }

    return key;
}

void handleInputs(Mouse& mouse, Window& window, Mesh& mesh) {
    // Misleading argument and function name combination. The input handling does not draw from the mouse or window at all, it simply does things with them

    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        if (event.type == SDL_QUIT) {
            window.requestClose();
        }

        SDL_Scancode key_scancode = event.key.keysym.scancode;
        if (key_scancode == SDL_SCANCODE_ESCAPE) {
            window.requestClose();
        }

        char key = getKeyboardInputCharacter(event);
        if (key == 'm'){
            mouse.toggleVisibility();
        } else if (key == 'c') {
            mouse.centerInWindow();
        } else if (key == 'h') {
            mesh.toggleVisibility();
        }

    }

}

int main(int argc, char* argv[]) {

    Window window(1600, 900, false);
    OpenGLContext gl_context(4, 1, window);
    Mouse mouse(window);

    VertexShader vs("src/shaders/temp.vs");
    FragmentShader fs("src/shaders/temp.fs");
    ShaderProgram shader(vs, fs);
    Mesh mesh(shader);

    // Display loop
    while(window.isOpen()) {
        mesh.draw();

        handleInputs(mouse, window, mesh);
        window.display();

    }

    // Close the window
    window.close();

    // Add a line break before going back to the terminal prompt.
    printf("\n");

    // Nothing went wrong!
    return 0;
}
