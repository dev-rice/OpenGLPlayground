#ifndef OpenGLContext_h
#define OpenGLContext_h

#include "includes/gl.hpp"
#include "includes/sdl.hpp"
#include "includes/glm.hpp"

#include "Window.hpp"

class OpenGLContext {
public:
    OpenGLContext(int major, int minor, Window& window);
    void setupGLEW();
    void enableDepthTest();
    void enableBackfaceCulling();
    void setupAlphaBlending();

private:

    void setDefaults();

    void setVersion(int major, int minor);
    void setupOpenGLContext(Window& window);
    void cleanup();

    SDL_GLContext gl_context;

};

#endif