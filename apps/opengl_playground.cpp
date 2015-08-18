#include "includes/gl.hpp"
#include "includes/sdl.hpp"
#include "Window.hpp"
#include "OpenGLContext.hpp"
#include "Mouse.hpp"
#include "Mesh.hpp"
#include "Camera.hpp"
#include "Drawable.hpp"
#include "VertexShaderCreator.hpp"
#include "FragmentShaderCreator.hpp"


#include <iostream>
#include <map>
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

glm::vec2 last_pos;
void rotateCameraFromMouse(Camera& camera, Mouse& mouse, Window& window) {
    glm::vec2 difference = mouse.getPosition() - last_pos;

    difference = difference * 0.001f;

    glm::vec3 rotation_vec(difference.y, -difference.x, 0);
    camera.rotateByLocal(rotation_vec);

    mouse.centerInWindow(window);
    last_pos = mouse.getPosition();
}

void handleInputs(Mouse& mouse, Window& window, Mesh& mesh, Camera& camera) {
    // Misleading argument and function name combination. The input handling does not draw from the mouse or window at all, it simply does things with them

    // Key repeat delay input
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
            mouse.centerInWindow(window);
        } else if (key == 'h') {
            mesh.toggleVisibility();
        }

    }

    // Continuous input
    const Uint8* keyboard = SDL_GetKeyboardState(NULL);

    glm::vec3 camera_movement(0, 0, 0);
    if (keyboard[SDL_SCANCODE_W]) {
        camera_movement += glm::vec3(0, 0, -1);
    }
    if (keyboard[SDL_SCANCODE_S]) {
        camera_movement += glm::vec3(0, 0, 1);
    }
    if (keyboard[SDL_SCANCODE_A]) {
        camera_movement += glm::vec3(-1, 0, 0);
    }
    if (keyboard[SDL_SCANCODE_D]) {
        camera_movement += glm::vec3(1, 0, 0);
    }
    if (keyboard[SDL_SCANCODE_SPACE]) {
        camera_movement += glm::vec3(0, 1, 0);
    }
    if (keyboard[SDL_SCANCODE_LSHIFT]) {
        camera_movement += glm::vec3(0, -1, 0);
    }

    if (glm::length(camera_movement) != 0){
        camera_movement = glm::normalize(camera_movement);
    }
    camera_movement = camera_movement * 0.1f;
    camera.moveByLocal(camera_movement);

    // Handle mouse rotation
    rotateCameraFromMouse(camera, mouse, window);

}

int main(int argc, char* argv[]) {

    Viewport viewport(1600, 900);
    Window window(viewport, false);
    OpenGLContext gl_context(4, 1, window);
    Mouse mouse;


    VertexShaderCreator vertex_shader_creator;
    FragmentShaderCreator fragment_shader_creator;

    ShaderFile vertex_shader("shaders/temp.vs", vertex_shader_creator);
    ShaderFile fragment_shader("shaders/temp.fs", fragment_shader_creator);
    ShaderProgram shader(vertex_shader, fragment_shader);

    float field_of_view = 45.0f;
    Camera camera(viewport, field_of_view);

    glm::vec3 camera_start_position(-1, 2, 6);
    camera.setPosition(camera_start_position);

    MeshLoader mesh_loader("res/castle_tower.dae");
    Mesh cube_mesh(mesh_loader);

    Drawable cube1(cube_mesh, shader);
    Drawable cube2(cube_mesh, shader);
    cube2.setPosition(glm::vec3(1, 1, 1));

    mouse.hide();
    mouse.centerInWindow(window);
    last_pos = mouse.getPosition();

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
