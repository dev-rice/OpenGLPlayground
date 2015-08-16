#ifndef Drawable_h
#define Drawable_h

#include "includes/gl.hpp"
#include "includes/glm.hpp"

#include "Camera.hpp"
#include "Mesh.hpp"

class Drawable {
public:
    Drawable(Mesh& mesh);

    Mesh& getMesh();
    glm::vec3 getPosition();

    void setPosition(glm::vec3 position);
    void draw(Camera& camera);
private:

    Mesh* mesh;
    glm::vec3 position;
};

#endif
