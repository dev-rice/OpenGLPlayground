#ifndef ParticleEmitter_h
#define ParticleEmitter_h

#include "Particle.hpp"
#include "Transform3D.hpp"
#include "Camera.hpp"

using namespace std;

class ParticleEmitter {
public:
    ParticleEmitter(Particle& to_be_emitted, Transform3D transform_3D);

    void fill(int number_of_particles);
    void draw(Camera& camera, GameClock& game_loop_clock);

    Transform3D& getTransform3D();

private:

    Particle& to_be_emitted;
    Transform3D transform_3D;
    vector<Particle> particles;

};

#endif
