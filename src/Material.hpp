#ifndef TextureManager_h
#define TextureManager_h

#include "includes/gl.hpp"

#include "Texture.hpp"
#include "ShaderProgram.hpp"

class Material {
public:
    Material(Texture& diffuse, Texture& emissive);

    void setTextureLocationsInShader(ShaderProgram& shader_program);
    void useTextures();

    Texture& getDiffuse();
    Texture& getEmissive();

private:

    Texture& diffuse;
    Texture& emissive;

};

#endif
