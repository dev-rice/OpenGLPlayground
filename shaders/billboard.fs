#version 330

in vec2 Texcoord;

out vec4 outColor;

// uniform float opacity;
uniform sampler2D diffuse_texture;

void main() {
    float opacity = 1.0;
    vec4 texel = texture(diffuse_texture, Texcoord);
    outColor = vec4(texel.rgb, opacity * texel.a);
}
