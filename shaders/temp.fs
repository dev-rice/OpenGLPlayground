#version 410 core

in vec3 Color;
in vec2 TextureCoordinates;

out vec4 outColor;

uniform sampler2D diffuse_texture;
uniform sampler2D emissive_texture;

void main() {
    vec4 diffuse_component = texture(diffuse_texture, TextureCoordinates);
    vec4 emissive_component = texture(emissive_texture, TextureCoordinates);
    vec4 emissive_opaque = vec4(emissive_component.rgb, 1);

    vec4 texel = mix(diffuse_component, emissive_opaque, emissive_component.a);
    outColor = texel;
}
