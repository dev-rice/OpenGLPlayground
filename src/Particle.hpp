#ifndef Particle_h
#define Particle_h

#include <cstdlib>
#include <ctime>

#include "Transform3D.hpp"
#include "MeshRenderer.hpp"
#include "Camera.hpp"
#include "GameClock.hpp"

using namespace std;

class Particle {
public:
    Particle(MeshRenderer drawable, Transform3D transform_3D);

    void draw(Camera& camera);

    void moveRandomDirection(GameClock& game_clock);

    MeshRenderer& getDrawable();
    Transform3D& getTransform3D();
private:

    float randomFloat(float a, float b);

    MeshRenderer drawable;
    Transform3D transform_3D;

};

#endif
