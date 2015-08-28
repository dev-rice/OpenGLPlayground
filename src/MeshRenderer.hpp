#ifndef MeshRenderer_h
#define MeshRenderer_h

#include "includes/gl.hpp"

#include "Camera.hpp"
#include "Mesh.hpp"
#include "ShaderProgram.hpp"
#include "Material.hpp"
#include "Transform3D.hpp"

class MeshRenderer {
public:
    MeshRenderer(Mesh& mesh, ShaderProgram& shader, Material& material);

    void draw(Camera& camera, Transform3D& transform_3D);

    void show();
    void hide();
    void toggleVisibility();
    bool isHidden();

    Mesh& getMesh();
    ShaderProgram& getShaderProgram();
    Material& getMaterial();

private:

    Mesh& mesh;
    ShaderProgram& shader;
    Material& material;

    bool is_hidden;

};

#endif
