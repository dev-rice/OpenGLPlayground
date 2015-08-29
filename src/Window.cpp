#include "Window.hpp"

Window::Window(Viewport& viewport, bool fullscreen) : viewport(viewport), fullscreen(fullscreen) {

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
        Viewport viewport_fullscreen = getFullscreenDimensions();
        setViewport(viewport_fullscreen);
    }
    this->fullscreen = fullscreen;
}

void Window::setWindowed() {
    // http://stackoverflow.com/questions/7193197/is-there-a-graceful-way-to-handle-toggling-between-fullscreen-and-windowed-mode
    setFullscreen(false);
}

int Window::getWidth() {
    return getViewport().getWidth();
}

int Window::getHeight() {
    return getViewport().getHeight();
}

Viewport Window::getFullscreenDimensions() {
    SDL_DisplayMode mode;
    SDL_GetDisplayMode(0, 0, &mode);
    Viewport viewport_fullscreen(mode.w, mode.h);

    return viewport_fullscreen;
}

Viewport& Window::getViewport() {
    return viewport;
}

void Window::setViewport(Viewport& viewport) {
    this->viewport = viewport;
}

bool Window::isFullscreen() {
    return fullscreen;
}


Uint32 Window::getCreationFlags() {
    Uint32 flags = SDL_WINDOW_SHOWN | SDL_WINDOW_OPENGL | SDL_WINDOW_BORDERLESS;

    if (isFullscreen()){
        flags |= SDL_WINDOW_FULLSCREEN;
    } else {
        flags |= SDL_WINDOW_ALLOW_HIGHDPI;
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
        SDL_WINDOWPOS_UNDEFINED, getViewport().getWidth(), getViewport().getHeight(), flags));
}

SDL_Window* Window::getSDLWindow() {
    return sdl_window;
}

void Window::initializeWindow(){
    createSDLWindow();
}

void Window::clearBuffers() {
    glClearColor(0, 0, 0, 1);
    clearDepthBuffer();
    clearColorBuffer();
}

void Window::clearDepthBuffer() {
    glClear(GL_DEPTH_BUFFER_BIT);
}

void Window::clearColorBuffer() {
    glClear(GL_COLOR_BUFFER_BIT);
}
