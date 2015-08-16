#include "includes/gl.hpp"
#include "includes/sdl.hpp"
#include "Window.hpp"
#include "OpenGLContext.hpp"
#include "Mouse.hpp"
#include "Mesh.hpp"
#include "Camera.hpp"
#include "Drawable.hpp"

#include <iostream>
#include <cstdio>

using namespace std;

char getKeyboardInputCharacter(SDL_Event& event) {

    char key = 0;
    if (event.type == SDL_KEYDOWN) {
        SDL_Keycode keycode = event.key.keysym.sym;
        key = keycode;
    }

    return key;
}

void handleInputs(Mouse& mouse, Window& window, Mesh& mesh, Camera& camera) {
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
        } else if (key == 'w') {
            camera.moveZ(-0.1);
        } else if (key == 's') {
            camera.moveZ(0.1);
        } else if (key == 'a') {
            camera.moveX(-0.1);
        } else if (key == 'd') {
            camera.moveX(0.1);
        } else if (key == 'z') {
            camera.moveY(0.1);
        } else if (key == 'x') {
            camera.moveY(-0.1);
        } else if (key == 'q') {
            camera.rotateY(0.1);
        } else if (key == 'e') {
            camera.rotateY(-0.1);
        } else if (key == 'r') {
            camera.rotateX(0.1);
        } else if (key == 'f') {
            camera.rotateX(-0.1);
        }

    }

}

int main(int argc, char* argv[]) {

    Viewport viewport(1600, 900);
    Window window(viewport, false);
    OpenGLContext gl_context(4, 1, window);
    Mouse mouse(window);

    VertexShader vs("shaders/temp.vs");
    FragmentShader fs("shaders/temp.fs");
    ShaderProgram shader(vs, fs);

    Mesh cube_mesh(shader);

    Drawable cube1(cube_mesh);
    Drawable cube2(cube_mesh);
    cube2.setPosition(glm::vec3(1, 1, 1));

    glm::vec3 pos(-1, 2, 4);
    glm::vec3 rot(0, 0, 0);
    float fov = 45.0f;
    Camera camera(viewport, pos, rot, fov);

    // Display loop
    while(window.isOpen()) {
        window.clearBuffers();

        cube1.draw(camera);
        cube2.draw(camera);

        handleInputs(mouse, window, cube_mesh, camera);
        window.display();

    }

    // Close the window
    window.close();

    // Nothing went wrong!
    return 0;
}
