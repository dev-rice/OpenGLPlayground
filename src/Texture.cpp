#include "Texture.hpp"

Texture::Texture(string filepath) {
    loadTextureFromFile(filepath, GL_LINEAR, true);
}

GLuint Texture::getGLId() {
    return gl_texture_id;
}

void Texture::bind(GLenum target) {
    glBindTexture(target, getGLId());
}

void Texture::create() {
    glGenTextures(1, &gl_texture_id);
}

void Texture::loadTextureFromBytes(GLubyte* data, GLuint width, GLuint height, GLuint filter, bool anisotropic_filtering){
    // Set the active texture
    create();
    bind(GL_TEXTURE_2D);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA,
                 GL_UNSIGNED_BYTE, data);

    // Set the texture wrapping to repeat
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    // Do nearest interpolation for scaling the image up and down.
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_NEAREST);

    // Min and max filter modes.
    if (!anisotropic_filtering){
        // When anisotropic filtering is off, it is best to set the minimizing filter as well as the maximizing filter
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, filter);
    }
    // Maximizing filter is good to do regardless of AF
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, filter);

    // Anisotropic filtering
    if (anisotropic_filtering){
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAX_ANISOTROPY_EXT, 4.0f);
    }

    // Mipmaps increase efficiency or something
    glGenerateMipmap(GL_TEXTURE_2D);

}

void Texture::loadTextureFromFile(string filename, GLuint filter, bool anisotropic_filtering){
    GLuint texture;

    string id = filename + std::to_string(filter);

    // Load the image
    int width, height;
    GLubyte* image = SOIL_load_image(filename.c_str(), &width, &height, 0, SOIL_LOAD_RGBA);

    loadTextureFromBytes(image, width, height, filter, anisotropic_filtering);
    SOIL_free_image_data(image);

}
