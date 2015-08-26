#ifndef TextureManager_h
#define TextureManager_h

#include "includes/gl.hpp"

#include "Texture.hpp"
#include "ShaderProgram.hpp"

class Material {
public:
    Material(Texture& diffuse);

    void setTextureLocationsInShader(ShaderProgram& shader_program);
    void useTextures();

    Texture& getDiffuse();

private:

    Texture* diffuse;

};

#endif
