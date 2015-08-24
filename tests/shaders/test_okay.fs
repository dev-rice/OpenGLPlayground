#version 410 core

in vec3 Color;
in vec2 TextureCoordinates;

out vec4 outColor;

uniform sampler2D diffuse_texture;

void main() {
    float color_length = length(Color);
    outColor = color_length * texture(diffuse_texture, TextureCoordinates);
}
