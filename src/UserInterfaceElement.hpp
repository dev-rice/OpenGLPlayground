#ifndef UserInterfaceElement_h
#define UserInterfaceElement_h

#include "includes/glm.hpp"

#include "Viewport.hpp"
#include "FlatDrawable.hpp"

using namespace std;

class UserInterfaceElement {
public:
    UserInterfaceElement(Viewport& viewport, FlatDrawable flat_drawable);

    Viewport& getViewport();
    FlatDrawable& getFlatDrawable();

    void draw();

    void setWidthInPixels(int width_in_pixels);
    void setHeightInPixels(int height_in_pixels);
    void setCenterInPixels(glm::vec2 center_in_pixels);

private:
    Viewport& viewport;
    FlatDrawable flat_drawable;
};

#endif
