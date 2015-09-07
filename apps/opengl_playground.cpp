#include "includes/gl.hpp"
#include "includes/sdl.hpp"
#include "Window.hpp"
#include "OpenGLContext.hpp"
#include "Mouse.hpp"
#include "Mesh.hpp"
#include "Camera.hpp"
#include "MeshRenderer.hpp"
#include "Texture.hpp"
#include "Material.hpp"
#include "ShaderProgramFactory.hpp"
#include "MouseCameraController.hpp"
#include "MeshFileParserDAE.hpp"
#include "MeshFileParserOBJ.hpp"
#include "VertexAttribute.hpp"
#include "MeshData.hpp"
#include "FlatDrawable.hpp"
#include "UserInterfaceElement.hpp"
#include "Transform3D.hpp"
#include "MeshFactory.hpp"
#include "GameClock.hpp"
#include "Unit.hpp"
#include "Particle.hpp"
#include "Doodad.hpp"
#include "ParticleEmitter.hpp"

#include <vector>
#include <iostream>
#include <cmath>
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

void handleInputs(Mouse& mouse, Window& window) {
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

}

int main(int argc, char* argv[]) {

    Viewport viewport(1600, 900);
    Window window(viewport, false);
    OpenGLContext gl_context(4, 1, window);
    Mouse mouse;

    window.setVsync(true);

    GameClock clock;

    SDL_version compiled;
    SDL_version linked;

    SDL_VERSION(&compiled);
    SDL_GetVersion(&linked);
    printf("We compiled against SDL version %d.%d.%d ...\n",
           compiled.major, compiled.minor, compiled.patch);
    printf("But we are linking against SDL version %d.%d.%d.\n",
           linked.major, linked.minor, linked.patch);

    cout << "GLEW Version: " << glewGetString(GLEW_VERSION) << "\n";

    ShaderProgramFactory shader_program_factory;
    ShaderProgram shader = shader_program_factory.createShaderProgram("shaders/temp.vs", "shaders/temp.fs");

    float field_of_view = 45.0f;
    float near_clip = 0.1f;
    float far_clip = 500.0f;
    Camera camera(viewport, Transform3D(), field_of_view, near_clip, far_clip);

    MouseCameraController mouse_camera_controller(mouse, camera.getTransform3D(), window, 0.1, 0.001);

    glm::vec3 camera_start_position(-1, 2, 6);
    #warning LoD violation
    camera.getTransform3D().setRelativePosition(camera_start_position);

    MeshFactory mesh_factory;
    Mesh castle_tower_mesh = mesh_factory.create3DMesh("res/castle_tower.dae");
    Mesh fence_mesh = mesh_factory.create3DMesh("res/fence.obj");

    Texture castle_tower_diffuse("res/castle_tower_diff.png");
    Texture castle_tower_emissive("res/blank.png");
    Material castle_tower_material(castle_tower_diffuse, castle_tower_emissive);

    Doodad castle_tower(MeshRenderer(castle_tower_mesh, shader, castle_tower_material), Transform3D());
    castle_tower.getTransform3D().setRelativePosition(glm::vec3(-4, 0, 1));
    castle_tower.getTransform3D().rotateByGlobal(glm::vec3(-M_PI / 2.0, 0, 0));

    Doodad castle_tower2(MeshRenderer(castle_tower_mesh, shader, castle_tower_material), Transform3D());
    castle_tower2.getTransform3D().setRelativePosition(glm::vec3(-4, 0, -5));
    castle_tower2.getTransform3D().rotateByGlobal(glm::vec3(-M_PI / 2.0, 0, 0));

    Texture fence_diffuse("res/fence_diff.png");
    Texture fence_emissive("res/blank.png");
    Material fence_material(fence_diffuse, fence_emissive);

    Doodad fence(MeshRenderer(fence_mesh, shader, fence_material), Transform3D());
    fence.getTransform3D().setRelativePosition(glm::vec3(2, 0, 1));

    ShaderProgram flat_shader = shader_program_factory.createShaderProgram("shaders/flat.vs", "shaders/flat.fs");

    Mesh flat_mesh = mesh_factory.createFlatMesh();

    UserInterfaceElement ui_element(viewport, FlatDrawable(flat_mesh, flat_shader), Transform2D());
    ui_element.setWidthInPixels(1600);
    ui_element.setHeightInPixels(60);
    ui_element.setCenterInPixels(glm::vec2(800, 30));

    Unit maligron(Transform3D(), 1000, 20);
    Unit yttrios(Transform3D(), 1500, 20);

    ShaderProgram billboard_shader = shader_program_factory.createShaderProgram("shaders/billboard.vs", "shaders/billboard.fs");
    Mesh billboard_mesh = mesh_factory.createBillboardMesh();
    Texture particle_diffuse("res/pink.png");
    Texture particle_emissive("res/fuzzyball.png");
    Material particle_material(particle_diffuse, particle_emissive);

    Particle to_be_emitted = Particle(MeshRenderer(billboard_mesh, billboard_shader, particle_material), Transform3D());
    ParticleEmitter particle_emitter(to_be_emitted, Transform3D());
    particle_emitter.fill(200);

    // Display loop
    while(window.isOpen()) {
        clock.tick();
        window.clearBuffers();

        castle_tower.draw(camera);
        castle_tower2.draw(camera);
        fence.draw(camera);

        particle_emitter.draw(camera, clock);

        particle_emitter.getTransform3D().moveByLocal(clock.getDeltaTime() * glm::vec3(0.1, 0, 0));

        ui_element.draw();

        castle_tower2.getTransform3D().rotateByGlobal(clock.getDeltaTime() * glm::vec3(0, M_PI/4.0, 0));

        handleInputs(mouse, window);
        mouse_camera_controller.update();
        window.display();

    }

    cout << "Average frame draw time: " << clock.getAverageDeltaTime() << "\n";
    float average_fps = 1.0f / clock.getAverageDeltaTime();
    cout << "Average frames per second: " << average_fps << "\n";

    // Close the window
    window.close();

    // Nothing went wrong!
    return 0;
}
