#include "Drawable.hpp"

Drawable::Drawable(MeshRenderer mesh_renderer, Transform3D transform_3D) : mesh_renderer(move(mesh_renderer)), transform_3D(move(transform_3D)) {


}

void Drawable::draw(Camera& camera) {
    getMeshRenderer().draw(camera, getTransform3D());
}

MeshRenderer& Drawable::getMeshRenderer() {
    return mesh_renderer;
}

Transform3D& Drawable::getTransform3D() {
    return transform_3D;
}
