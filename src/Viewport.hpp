#ifndef Viewport_h
#define Viewport_h

#include "includes/glm.hpp"

class Viewport {
public:
    Viewport(int w, int h);

    int getWidth();
    int getHeight();

    glm::vec2 getCenter();
    float getAspectRatio();

private:
    int width;
    int height;
};

#endif
