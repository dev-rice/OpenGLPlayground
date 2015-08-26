#include "Material.hpp"

Material::Material(Texture& diffuse) : diffuse(&diffuse) {

}

void Material::setTextureLocationsInShader(ShaderProgram& shader_program) {

    glUniform1i(shader_program.getUniformLocation("diffuse_texture"), 0);

}

void Material::useTextures() {
    glActiveTexture(GL_TEXTURE0);
    getDiffuse().bind(GL_TEXTURE_2D);
}

Texture& Material::getDiffuse() {
    return *diffuse;
}
