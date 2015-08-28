#ifndef Drawable_h
#define Drawable_h

#include "MeshRenderer.hpp"
#include "Transform3D.hpp"
#include "Camera.hpp"

using namespace std;

class Drawable {
public:
    Drawable(MeshRenderer mesh_renderer, Transform3D transform_3D);

    void draw(Camera& camera);

    MeshRenderer& getMeshRenderer();
    Transform3D& getTransform3D();
private:

    MeshRenderer mesh_renderer;
    Transform3D transform_3D;
};

#endif
