#ifndef Drawable_h
#define Drawable_h

#include "includes/gl.hpp"
#include "includes/glm.hpp"

#include "Camera.hpp"
#include "Mesh.hpp"
#include "ShaderProgram.hpp"

class Drawable {
public:
    Drawable(Mesh& mesh, ShaderProgram& shader);

    void draw(Camera& camera);

    void setPosition(glm::vec3 position);

    Mesh& getMesh();
    glm::vec3 getPosition();
    ShaderProgram& getShaderProgram();
private:

    Mesh* mesh;
    ShaderProgram* shader;

    glm::vec3 position;
};

#endif
