#version 410 core

in vec2 position;
in vec2 texture_coordinates;

out vec2 TextureCoordinates;

uniform mat3 transformation;

void main() {
    vec3 position_temp = vec3(position, 1.0) * transformation;
    gl_Position = vec4(position_temp.xy, 0.0, 1.0);
}
