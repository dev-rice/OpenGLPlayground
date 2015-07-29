#include "window.hpp"

Window::Window(int width, int height, bool fullscreen){

    setWidth(width);
    setHeight(height);
    setFullscreen(fullscreen);
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
    SDL_GL_DeleteContext(gl_context);
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

void Window::setupOpenGLContext(int major, int minor) {
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
    SDL_GL_SetAttribute( SDL_GL_CONTEXT_MAJOR_VERSION, major );
    SDL_GL_SetAttribute( SDL_GL_CONTEXT_MINOR_VERSION, minor );

    setGLContext(SDL_GL_CreateContext(getSDLWindow()));

    setupGLEW();

}

void Window::setupGLEW() {
    // GLEW lets us use abstracted OpenGL functions
    glewExperimental = GL_TRUE;
    glewInit();
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

void Window::setGLContext(SDL_GLContext gl_context) {
    this->gl_context = gl_context;
}

void Window::createSDLWindow() {
    Uint32 flags = getCreationFlags();

    SDL_Init(SDL_INIT_EVERYTHING);

    setSDLWindow(SDL_CreateWindow("Game", SDL_WINDOWPOS_UNDEFINED,
        SDL_WINDOWPOS_UNDEFINED, width, height, flags));
}

void Window::enableDepthTest() {
    // Set up the correct depth rendering
    glEnable(GL_DEPTH_TEST);
}

void Window::enableBackfaceCulling() {
    // Describe what constitutes the front face, and enable backface culling
    glFrontFace(GL_CCW);
    glEnable(GL_CULL_FACE);
}

void Window::setupAlphaBlending() {
    // Alpha transparency
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);
}

SDL_Window* Window::getSDLWindow() {
    return sdl_window;
}

SDL_GLContext Window::getGLContext() {
    return gl_context;
}

void Window::initializeWindow(){
    createSDLWindow();
    setupOpenGLContext(4, 1);

    centerMouse();
    showMouse();

    // Print various info about OpenGL
    // Debug::info("Renderer:       %s\n", glGetString(GL_RENDERER));
    // Debug::info("OpenGL version: %s\n", glGetString(GL_VERSION));
    // Debug::info("GLSL version:   %s\n", glGetString(GL_SHADING_LANGUAGE_VERSION));
    enableDepthTest();
    enableBackfaceCulling();
    setupAlphaBlending();

}

bool Window::isMouseHidden() {
    return is_mouse_hidden;
}

void Window::hideMouse() {
    is_mouse_hidden = true;
    SDL_ShowCursor(SDL_DISABLE);
}

void Window::showMouse() {
    is_mouse_hidden = false;
    SDL_ShowCursor(SDL_ENABLE);
}

void Window::toggleMouse() {
    if (isMouseHidden()) {
        showMouse();
    } else {
        hideMouse();
    }
}

void Window::setMousePosition(int x, int y){
    SDL_WarpMouseInWindow(getSDLWindow(), x, y);
}

void Window::centerMouse(){
    setMousePosition(getWidth() / 2, getHeight() / 2);
}
