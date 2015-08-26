#ifndef Drawable_h
#define Drawable_h

#include "includes/gl.hpp"

#include "Camera.hpp"
#include "Mesh.hpp"
#include "ShaderProgram.hpp"
#include "Material.hpp"
#include "Transform3D.hpp"

class Drawable {
public:
    Drawable(Mesh& mesh, ShaderProgram& shader, Material& texture_manager);

    void draw(Camera& camera, Transform3D& transform_3D);

    void show();
    void hide();
    void toggleVisibility();
    bool isHidden();

    Mesh& getMesh();
    ShaderProgram& getShaderProgram();
    Material& getTextureManager();

private:

    Mesh* mesh;
    ShaderProgram* shader;
    Material* texture_manager;

    bool is_hidden;

};

#endif
