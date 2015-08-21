#version 410 core

layout(location=1) in vec3 position;
layout(location=2) in vec3 normal;
layout(location=3) in vec2 texture_coordinates;

out vec3 Color;
out vec2 TextureCoordinates;

uniform mat4 model;
uniform mat4 view;
uniform mat4 proj;

void main() {
   Color = normal;
   TextureCoordinates = texture_coordinates;
   gl_Position =  proj * view * model * vec4(position, 1.0);
}
