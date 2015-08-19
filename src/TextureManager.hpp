#ifndef TextureManager_h
#define TextureManager_h

#include "includes/gl.hpp"

#include "Texture.hpp"
#include "ShaderProgram.hpp"

class TextureManager {
public:
    TextureManager(Texture& diffuse);

    void setTextureLocationsInShader(ShaderProgram& shader_program);
    void activate();

    Texture& getDiffuse();

private:

    Texture* diffuse;

};

#endif
