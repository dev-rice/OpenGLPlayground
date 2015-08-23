#ifndef FlatDrawable_h
#define FlatDrawable_h

#include "Mesh.hpp"
#include "ShaderProgram.hpp"
#include "Transform2D.hpp"

class FlatDrawable {
public:
    FlatDrawable(Mesh& mesh, ShaderProgram& shader_program, Transform2D& transform_2D);

    void draw();

    Mesh& getMesh();
    ShaderProgram& getShaderProgram();
    Transform2D& getTransform2D();

private:

    Mesh* mesh;
    ShaderProgram* shader_program;
    Transform2D* transform_2D;

};

#endif
