#version 330

in vec3 position;
in vec2 texture_coordinates;

out vec2 Texcoord;

uniform mat4 model;
uniform mat4 view;
uniform mat4 proj;

uniform float time;
uniform float plane_rotation;

mat4 rotationMatrix(vec3 axis, float angle) {
    axis = normalize(axis);
    float s = sin(angle);
    float c = cos(angle);
    float oc = 1.0 - c;

    return mat4(oc * axis.x * axis.x + c,           oc * axis.x * axis.y - axis.z * s,  oc * axis.z * axis.x + axis.y * s,  0.0,
                oc * axis.x * axis.y + axis.z * s,  oc * axis.y * axis.y + c,           oc * axis.y * axis.z - axis.x * s,  0.0,
                oc * axis.z * axis.x - axis.y * s,  oc * axis.y * axis.z + axis.x * s,  oc * axis.z * axis.z + c,           0.0,
                0.0,                                0.0,                                0.0,                                1.0);
}

void main(){
    Texcoord = texture_coordinates;

    mat4 rotation_matrix = mat4( view[0][0], view[1][0], view[2][0], 0.0,
                                 view[0][1], view[1][1], view[2][1], 0.0,
                                 view[0][2], view[1][2], view[2][2], 0.0,
                                 0.0       , 0.0       , 0.0       , 1.0);

    vec4 planar_rotation_axis = rotation_matrix * vec4(0.0, 0.0, 1.0, 1.0);
    mat4 planar_rotation_matrix = rotationMatrix(planar_rotation_axis.xyz, plane_rotation);

    vec4 world_position = rotation_matrix * vec4(position, 1.0);
    world_position = planar_rotation_matrix * world_position;
    world_position = model * world_position;

    gl_Position = proj * view * world_position;

}
