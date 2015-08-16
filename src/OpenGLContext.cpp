#include "OpenGLContext.hpp"

OpenGLContext::OpenGLContext(int major, int minor, Window& window) {
    setVersion(major, minor);
    setupOpenGLContext(window);
    setDefaults();
    printVersionInformation();
}

void OpenGLContext::setVersion(int major, int minor) {
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
    SDL_GL_SetAttribute( SDL_GL_CONTEXT_MAJOR_VERSION, major );
    SDL_GL_SetAttribute( SDL_GL_CONTEXT_MINOR_VERSION, minor );
}

void OpenGLContext::setupOpenGLContext(Window& window) {

    SDL_GLContext context = SDL_GL_CreateContext(window.getSDLWindow());

    setupGLEW();

}

void OpenGLContext::setupGLEW() {
    // GLEW lets us use abstracted OpenGL functions
    glewExperimental = GL_TRUE;
    glewInit();
}

void OpenGLContext::enableDepthTest() {
    // Set up the correct depth rendering
    glEnable(GL_DEPTH_TEST);
}

void OpenGLContext::enableBackfaceCulling() {
    // Describe what constitutes the front face, and enable backface culling
    glFrontFace(GL_CCW);
    glEnable(GL_CULL_FACE);
}

void OpenGLContext::setupAlphaBlending() {
    // Alpha transparency
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);
}

void OpenGLContext::setDefaults() {
    setupAlphaBlending();
    enableDepthTest();
    enableBackfaceCulling();
}

void OpenGLContext::cleanup() {
    SDL_GL_DeleteContext(gl_context);
}

string OpenGLContext::getRendererString() {
    return string(reinterpret_cast<const char*>(glGetString(GL_RENDERER)));
}

string OpenGLContext::getVersionString() {
    return string(reinterpret_cast<const char*>(glGetString(GL_VERSION)));
}

string OpenGLContext::getGLSLVersionString() {
    return string(reinterpret_cast<const char*>(glGetString(GL_SHADING_LANGUAGE_VERSION)));
}

void OpenGLContext::printVersionInformation() {
    // Print various info about OpenGL
    cout << "Renderer: " << getRendererString() << "\n";
    cout << "OpenGL version: " << getVersionString() << "\n";
    cout << "GLSL version: " << getGLSLVersionString() << "\n";
}
