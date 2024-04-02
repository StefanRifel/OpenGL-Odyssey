#version 330 core

layout (location = 0) in vec3 aPos;
layout (location = 1) in float vertValue;

out float fragValue;

void main(void) {
    gl_Position = vec4(aPos, 1.0);
    fragValue = vertValue;
}