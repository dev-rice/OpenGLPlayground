#ifndef Mesh_h
#define Mesh_h

#include "includes/gl.hpp"
#include "includes/glm.hpp"

class Mesh {
public:
    Mesh();
    void draw();
    void clearBuffer();
    void show();
    void hide();
    void toggle();
    bool isHidden();
private:
    bool is_hidden;
};

#endif
