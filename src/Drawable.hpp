#ifndef Drawable_h
#define Drawable_h

#include "includes/gl.hpp"
#include "includes/glm.hpp"

#include "Camera.hpp"
#include "Mesh.hpp"
#include "ShaderProgram.hpp"
#include "Texture.hpp"

class Drawable {
public:
    Drawable(Mesh& mesh, ShaderProgram& shader, Texture& diffuse);

    void draw(Camera& camera);

    void moveByGlobal(glm::vec3 move_vector);

    void rotateByGlobal(glm::vec3 rotation_vec);

    void setPosition(glm::vec3 position);
    void setRotationInGlobalCoordinates(glm::vec3 rotation_in_global_coordinates);

    glm::vec3 getPosition();
    glm::vec3 getRotationInGlobalCoordinates();


    Mesh& getMesh();
    ShaderProgram& getShaderProgram();
private:

    void setDiffuse(Texture& texture);
    Texture& getDiffuse();

    glm::mat4 calculateModelMatrix();
    glm::mat4 calculateRotationMatrix();
    glm::mat4 calculateTranslationMatrix();

    Mesh* mesh;
    ShaderProgram* shader;
    Texture* diffuse;

    glm::vec3 position;
    glm::vec3 rotation_in_global_coordinates;
};

#endif
