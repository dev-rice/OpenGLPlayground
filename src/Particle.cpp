#include "Particle.hpp"

// THIS CLASS KNOWS TOO MUCH:
//      How to construct a Transform3D (even though this is simple)
//      How to construct a Drawable, given a Mesh, a ShaderProgram, a Material, and a Transform3D
//      How to tell a Drawable to draw, given a Camera
//      How to make low level OpenGL calls to make itself draw correctly
// BUT IT WORKS SO IDK WHAT'S RIGHT

Particle::Particle(Mesh& mesh, ShaderProgram& shader_program, Material& textures) : transform_3D(), drawable(mesh, shader_program, textures) {

    srand(time(NULL));

}

void Particle::draw(Camera& camera) {
    glDepthFunc(GL_LEQUAL);
    glDepthMask(GL_FALSE);

    getDrawable().draw(camera, transform_3D);

    glDepthFunc(GL_LESS);
    glDepthMask(GL_TRUE);
}

void Particle::moveRandomDirection(GameClock& game_clock) {
    glm::vec3 direction(randomFloat(-1.0, 1.0), randomFloat(-1.0, 1.0), randomFloat(-1.0, 1.0));
    glm::vec3 time_adjusted_direction = game_clock.getDeltaTime() * direction;
    getTransform3D().moveByGlobal(time_adjusted_direction);
}

float Particle::randomFloat(float a, float b) {
    float random = ((float) rand()) / (float) RAND_MAX;
    float diff = b - a;
    float r = random * diff;
    return a + r;
}

Drawable& Particle::getDrawable() {
    return drawable;
}

Transform3D& Particle::getTransform3D() {
    return transform_3D;
}