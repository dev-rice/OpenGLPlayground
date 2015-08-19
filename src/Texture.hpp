#ifndef Texture_h
#define Texture_h

#include <string>

#include "includes/gl.hpp"
#include "includes/sdl.hpp"
#include "includes/soil.hpp"

using namespace std;

class Texture {
public:
    Texture(string filepath);

    GLuint getGLId();
    void bind(GLenum target);
private:

    GLuint loadTextureFromBytes(GLubyte* data, GLuint width, GLuint height, GLuint filter, bool anisotropic_filtering);

    GLuint loadTextureFromFile(string filepath, GLuint filter, bool anisotropic_filtering);

    GLuint gl_texture_id;

};

#endif
