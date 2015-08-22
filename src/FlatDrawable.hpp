#ifndef FlatDrawable_h
#define FlatDrawable_h

#include "Mesh.hpp"
#include "ShaderProgram.hpp"

class FlatDrawable {
public:
    FlatDrawable(Mesh& mesh, ShaderProgram& shader_program);

    void draw();

    void setWidth(float width);
    void setHeight(float height);
    void setPositionOfCenter(glm::vec2 position_of_center);

    float getWidth();
    float getHeight();
    glm::vec2 getPositionOfCenter();
    Mesh& getMesh();
    ShaderProgram& getShaderProgram();

private:

    float width;
    float height;
    glm::vec2 position_of_center;
    Mesh* mesh;
    ShaderProgram* shader_program;

};

#endif
