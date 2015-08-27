#ifndef Particle_h
#define Particle_h

#include <cstdlib>
#include <ctime>

#include "Texture.hpp"
#include "Material.hpp"
#include "Transform3D.hpp"
#include "Drawable.hpp"
#include "Camera.hpp"
#include "Mesh.hpp"
#include "ShaderProgram.hpp"
#include "GameClock.hpp"

using namespace std;

class Particle {
public:
    Particle(Drawable drawable, Transform3D transform_3D);

    void draw(Camera& camera);

    void moveRandomDirection(GameClock& game_clock);

    Drawable& getDrawable();
    Transform3D& getTransform3D();
private:

    float randomFloat(float a, float b);

    Drawable drawable;
    Transform3D transform_3D;

};

#endif
