#include "Material.hpp"

Material::Material(Texture& diffuse) : diffuse(&diffuse) {

}

void Material::setTextureLocationsInShader(ShaderProgram& shader_program) {
    shader_program.use();
    glUniform1i(shader_program.getUniformLocation("diffuse_texture"), 1);

}

void Material::useTextures() {
    glActiveTexture(GL_TEXTURE1);
    getDiffuse().bind(GL_TEXTURE_2D);
}

Texture& Material::getDiffuse() {
    return *diffuse;
}
