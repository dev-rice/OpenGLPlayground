#ifndef Window_h
#define Window_h

#include "includes/gl.hpp"
#include "includes/sdl.hpp"
#include "includes/glm.hpp"

#include <SOIL.h>
#include <ctime>
#include <string>
#include <iostream>

#include "Viewport.hpp"

using namespace std;

class Window {
public:
    Window(Viewport& viewport, bool fullscreen);

    void initializeWindow();
    void display();
    void close();

    void clearBuffers();

    void requestClose();
    bool shouldClose();
    bool isOpen();

    void setFullscreen(bool fullscreen);
    void setWindowed();
    void setVsync(bool);

    int getWidth();
    int getHeight();

    void setViewport(Viewport& viewport);

    bool isFullscreen();

    SDL_Window* getSDLWindow();
    Viewport& getViewport();

private:

    void clearDepthBuffer();
    void clearColorBuffer();

    void setShouldClose(bool should_close);
    void setSDLWindow(SDL_Window* sdl_window);

    Uint32 getCreationFlags();
    void createSDLWindow();

    Viewport getFullscreenDimensions();

    Viewport* viewport;
    bool fullscreen;

    bool should_close;

    SDL_Window* sdl_window;

};

#endif
