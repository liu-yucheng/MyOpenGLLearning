// Copyright 2022 Yucheng Liu. GNU GPL3 license.
// GNU GPL3 license copy: https://www.gnu.org/licenses/gpl-3.0.txt

#version 140
#extension GL_ARB_explicit_attrib_location: require
#extension GL_ARB_explicit_uniform_location: require

in vec4 color;

void main() {
    gl_FragColor = color;
}
