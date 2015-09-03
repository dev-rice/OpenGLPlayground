#include "ParticleEmitter.hpp"

ParticleEmitter::ParticleEmitter(Particle& to_be_emitted, Transform3D transform_3D) : to_be_emitted(to_be_emitted), transform_3D(move(transform_3D)) {

}

void ParticleEmitter::fill(int number_of_particles) {
    for (int i = 0; i < number_of_particles; ++i) {
        particles.push_back(Particle(to_be_emitted));
        particles[i].getTransform3D().setParent(getTransform3D());
    }
}

void ParticleEmitter::draw(Camera& camera, GameClock& game_loop_clock) {
    for (Particle& particle : particles) {
        particle.draw(camera);
        particle.moveRandomDirection(game_loop_clock);
    }
}

Transform3D& ParticleEmitter::getTransform3D() {
    return transform_3D;
}
