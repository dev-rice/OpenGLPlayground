#version 410 core

in vec3 position;
in vec3 normal;
in vec2 texture_coordinate;

out vec3 Color;

uniform mat4 model;
uniform mat4 view;
uniform mat4 proj;

void main() {
   Color = normal;
   gl_Position =  proj * view * model * vec4(position, 1.0);
}
