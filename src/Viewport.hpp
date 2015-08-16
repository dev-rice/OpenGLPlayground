#ifndef Viewport_h
#define Viewport_h

class Viewport {
public:
    Viewport(int w, int h);

    int getWidth();
    int getHeight();

private:
    int width;
    int height;
};

#endif
