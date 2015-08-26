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

class Particle {
public:
    Particle(Mesh& mesh, ShaderProgram& shader_program, Material& textures);

    void draw(Camera& camera);

    void moveRandomDirection(GameClock& game_clock);

    Drawable& getDrawable();
    Transform3D& getTransform3D();
private:

    float randomFloat(float a, float b);

    Transform3D transform_3D;
    Drawable drawable;

};

#endif
