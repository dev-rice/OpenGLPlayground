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
#include "MeshFileParserDAE.hpp"
#include "MeshFileParserOBJ.hpp"
#include "Texture.hpp"
#include "TextureManager.hpp"
#include "ShaderProgramFactory.hpp"
#include "MeshFactory.hpp"

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

void rotateCameraFromMouse(Camera& camera, Mouse& mouse, Window& window) {
    glm::vec2 difference = mouse.getPosition() - window.getViewport().getCenter();

    difference = difference * 0.001f;

    glm::vec3 rotation_vec(difference.y, -difference.x, 0);
    camera.rotateByLocal(rotation_vec);

    mouse.centerInWindow(window);
}

void handleInputs(Mouse& mouse, Window& window, Camera& camera) {
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

    ShaderProgramFactory shader_program_factory;
    ShaderProgram shader = shader_program_factory.createShaderProgram("shaders/temp.vs", "shaders/temp.fs");

    float field_of_view = 45.0f;
    float near_clip = 0.1f;
    float far_clip = 500.0f;
    Camera camera(viewport, field_of_view, near_clip, far_clip);

    glm::vec3 camera_start_position(-1, 2, 6);
    camera.setPosition(camera_start_position);

    MeshFactory mesh_factory;
    Mesh castle_tower_mesh = mesh_factory.createMesh("res/castle_tower.dae");

    Texture castle_tower_diffuse("res/castle_tower_diff.png");
    TextureManager castle_tower_textures(castle_tower_diffuse);
    Drawable castle_tower1(castle_tower_mesh, shader, castle_tower_textures);
    castle_tower1.setRotationInGlobalCoordinates(glm::vec3(3.1415927 / 2.0, 0, 0));

    Drawable castle_tower2(castle_tower_mesh, shader, castle_tower_textures);
    castle_tower2.setPosition(glm::vec3(-4, 0, 1));
    castle_tower2.setRotationInGlobalCoordinates(glm::vec3(3.1415927 / 2.0, 0, 0));

    Mesh fence_mesh = mesh_factory.createMesh("res/fence.obj");

    Texture fence_diffuse("res/fence_diff.png");
    TextureManager fence_textures(fence_diffuse);
    Drawable fence(fence_mesh, shader, fence_textures);
    fence.setPosition(glm::vec3(2, 0, 1));

    mouse.hide();
    mouse.centerInWindow(window);

    // Display loop
    while(window.isOpen()) {
        window.clearBuffers();

        castle_tower1.draw(camera);
        castle_tower2.draw(camera);
        fence.draw(camera);

        castle_tower1.rotateByGlobal(glm::vec3(0, 0.01, 0));

        handleInputs(mouse, window, camera);
        window.display();

    }

    // Close the window
    window.close();

    // Nothing went wrong!
    return 0;
}
