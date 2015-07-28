#include "includes/gl.hpp"
#include "includes/sdl.hpp"
#include "window.hpp"

#include <iostream>

using namespace std;

int main(int argc, char* argv[]) {

    Window our_window(1600, 900, false);

    // Display loop
    while(our_window.isOpen()) {
        SDL_Event event;
        SDL_PollEvent(&event);

        SDL_Scancode key_scancode = event.key.keysym.scancode;
        if (event.type == SDL_QUIT) {
            our_window.requestClose();
        }
        if (key_scancode == SDL_SCANCODE_ESCAPE) {
            our_window.requestClose();
        }
        if (key_scancode == SDL_SCANCODE_M) {
            our_window.hideMouse();
        }

        our_window.display();

    }

    // Close the window
    our_window.close();

    // Add a line break before going back to the terminal prompt.
    printf("\n");

    // Nothing went wrong!
    return 0;
}
