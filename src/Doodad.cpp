#include "Doodad.hpp"

Doodad::Doodad(MeshRenderer mesh_renderer, Transform3D transform_3D) : mesh_renderer(move(mesh_renderer)), transform_3D(move(transform_3D)) {


}

void Doodad::draw(Camera& camera) {
    getMeshRenderer().draw(camera, getTransform3D());
}

MeshRenderer& Doodad::getMeshRenderer() {
    return mesh_renderer;
}

Transform3D& Doodad::getTransform3D() {
    return transform_3D;
}
