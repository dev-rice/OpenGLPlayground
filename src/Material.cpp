#include "Material.hpp"

Material::Material(Texture& diffuse, Texture& emissive) : diffuse(&diffuse), emissive(&emissive) {

}

void Material::setTextureLocationsInShader(ShaderProgram& shader_program) {
    shader_program.use();
    glUniform1i(shader_program.getUniformLocation("diffuse_texture"), 0);
    glUniform1i(shader_program.getUniformLocation("emissive_texture"), 1);

}

void Material::useTextures() {
    glActiveTexture(GL_TEXTURE0);
    getDiffuse().bind(GL_TEXTURE_2D);

    glActiveTexture(GL_TEXTURE1);
    getEmissive().bind(GL_TEXTURE_2D);
}

Texture& Material::getDiffuse() {
    return *diffuse;
}

Texture& Material::getEmissive() {
    return *emissive;
}
