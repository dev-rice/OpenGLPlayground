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

    void moveByGlobal(glm::vec3 move_vector);

    void rotateByGlobal(glm::vec3 rotation_vec);

    void setPosition(glm::vec3 position);
    void setRotationInGlobalCoordinates(glm::vec3 rotation_in_global_coordinates);

    glm::vec3 getPosition();
    glm::vec3 getRotation();

    Mesh& getMesh();
    ShaderProgram& getShaderProgram();
private:

    glm::mat4 calculateModelMatrix();
    glm::mat4 calculateRotationMatrix();
    glm::mat4 calculateTranslationMatrix();

    Mesh* mesh;
    ShaderProgram* shader;

    glm::vec3 position;
    glm::vec3 rotation_in_global_coordinates;
};

#endif
