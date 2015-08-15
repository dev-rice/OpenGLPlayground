#include "Window.hpp"

Window::Window(int width, int height, bool fullscreen) : width(width), height(height), fullscreen(fullscreen) {

    setShouldClose(false);
    initializeWindow();

}

void Window::display(){
    //Update screen
    SDL_GL_SwapWindow(getSDLWindow());
}

void Window::requestClose() {
    setShouldClose(true);
}

void Window::setShouldClose(bool should_close){
    this->should_close = should_close;
}

bool Window::shouldClose(){
    return should_close;
}

bool Window::isOpen() {
    return !shouldClose();
}

void Window::close(){
    // Quit SDL
    SDL_DestroyWindow(getSDLWindow());
    SDL_Quit();
}

void Window::setVsync(bool value){
    if (value){
        SDL_GL_SetSwapInterval(1);
    } else {
        SDL_GL_SetSwapInterval(0);
    }
}

void Window::setFullscreen(bool fullscreen){
    if (fullscreen){
        WindowDimensions dim = getFullscreenDimensions();
        setWidth(dim.width);
        setHeight(dim.height);
    }
    this->fullscreen = fullscreen;
}

void Window::setWindowed() {
    // http://stackoverflow.com/questions/7193197/is-there-a-graceful-way-to-handle-toggling-between-fullscreen-and-windowed-mode
    setFullscreen(false);
}

WindowDimensions Window::getFullscreenDimensions() {
    SDL_DisplayMode mode;
    SDL_GetDisplayMode(0, 0, &mode);
    WindowDimensions dim(mode.w, mode.h);

    return dim;
}

void Window::setWidth(int width){
    this->width = width;
}

void Window::setHeight(int height){
    this->height = height;
}

int Window::getWidth(){
    return width;
}

int Window::getHeight(){
    return height;
}

bool Window::isFullscreen() {
    return fullscreen;
}


Uint32 Window::getCreationFlags() {
    Uint32 flags = SDL_WINDOW_SHOWN | SDL_WINDOW_OPENGL;

    if (isFullscreen()){
        flags |= SDL_WINDOW_FULLSCREEN;
    }

    return flags;
}

void Window::setSDLWindow(SDL_Window* sdl_window) {
    this->sdl_window = sdl_window;
}

void Window::createSDLWindow() {
    Uint32 flags = getCreationFlags();

    SDL_Init(SDL_INIT_EVERYTHING);

    setSDLWindow(SDL_CreateWindow("Game", SDL_WINDOWPOS_UNDEFINED,
        SDL_WINDOWPOS_UNDEFINED, width, height, flags));
}

SDL_Window* Window::getSDLWindow() {
    return sdl_window;
}

void Window::initializeWindow(){
    createSDLWindow();
}
