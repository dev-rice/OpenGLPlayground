#ifndef Doodad_h
#define Doodad_h

#include "MeshRenderer.hpp"
#include "Transform3D.hpp"
#include "Camera.hpp"

using namespace std;

class Doodad {
public:
    Doodad(MeshRenderer mesh_renderer, Transform3D transform_3D);

    void draw(Camera& camera);

    MeshRenderer& getMeshRenderer();
    Transform3D& getTransform3D();
private:

    MeshRenderer mesh_renderer;
    Transform3D transform_3D;
};

#endif
