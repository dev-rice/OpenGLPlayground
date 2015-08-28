#ifndef FlatDrawable_h
#define FlatDrawable_h

#include "includes/gl.hpp"

#include "Mesh.hpp"
#include "ShaderProgram.hpp"
#include "Transform2D.hpp"

class FlatDrawable {
public:
    FlatDrawable(Mesh& mesh, ShaderProgram& shader_program);

    void draw(Transform2D& transform_2D);

    void show();
    void hide();
    void toggleVisibility();
    bool isHidden();

    Mesh& getMesh();
    ShaderProgram& getShaderProgram();

private:

    Mesh& mesh;
    ShaderProgram& shader_program;

    bool is_hidden;

};

#endif
