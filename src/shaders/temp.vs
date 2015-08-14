#version 150 core

in vec2 position;
in vec3 in_color;
out vec3 frag_color;

void main() {
    frag_color = in_color;
    gl_Position = vec4(position, 0.0, 1.0);
}
