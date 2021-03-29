#version 140
#extension GL_ARB_explicit_attrib_location: require
#extension GL_ARB_explicit_uniform_location: require

layout (location = 0) in vec3 position;
uniform mat4 mapping;
out vec4 color;

void main() {
    gl_Position = mapping * vec4(position, 1.0);
    color = vec4(clamp(position, 0.0, 1.0), 1.0);
}
