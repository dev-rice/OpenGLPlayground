#include "TextureManager.hpp"

TextureManager::TextureManager(Texture& diffuse) : diffuse(&diffuse) {

}

void TextureManager::setTextureLocationsInShader(ShaderProgram& shader_program) {

    glUniform1i(shader_program.getUniformLocation("diffuse_texture"), 0);

}

void TextureManager::useTextures() {
    glActiveTexture(GL_TEXTURE0);
    getDiffuse().bind(GL_TEXTURE_2D);
}

Texture& TextureManager::getDiffuse() {
    return *diffuse;
}
