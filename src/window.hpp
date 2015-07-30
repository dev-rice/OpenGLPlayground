#ifndef Window_h
#define Window_h

#include "includes/gl.hpp"
#include "includes/sdl.hpp"
#include "includes/glm.hpp"

#include <SOIL.h>
#include <ctime>
#include <string>
#include <iostream>

using namespace std;

struct WindowDimensions {
    WindowDimensions(int w, int h) {
        width = w;
        height = h;
    }
    int width;
    int height;
};

class Window {
public:
    Window(int width, int height, bool fullscreen);

    void initializeWindow();
    void display();
    void close();

    void requestClose();
    bool shouldClose();
    bool isOpen();

    void hideMouse();
    void showMouse();
    void toggleMouse();
    bool isMouseHidden();
    void setMousePosition(int x, int y);
    void centerMouse();

    void setFullscreen(bool fullscreen);
    void setWindowed();
    void setVsync(bool);

    SDL_Window* getSDLWindow();
    SDL_GLContext getGLContext();

    int getWidth();
    int getHeight();
    bool isFullscreen();

private:

    void setShouldClose(bool should_close);
    void setSDLWindow(SDL_Window* sdl_window);
    void setGLContext(SDL_GLContext gl_context);
    void setupOpenGLContext(int major, int minor);
    void setupGLEW();
    Uint32 getCreationFlags();
    void createSDLWindow();
    void enableDepthTest();
    void enableBackfaceCulling();
    void setupAlphaBlending();

    void setWidth(int w);
    void setHeight(int h);

    WindowDimensions getFullscreenDimensions();

    int width;
    int height;
    bool fullscreen;
    bool is_mouse_hidden;

    int requested_width;
    int requested_height;

    bool should_close;

    SDL_Window* sdl_window;
    SDL_GLContext gl_context;

};

#endif
