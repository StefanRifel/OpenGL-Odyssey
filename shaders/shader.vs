#version 330 core

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aColor;
layout (location = 2) in vec2 aTexCoord;

out vec3 vertexColor;
out vec2 texCoord;

uniform vec3 color;
uniform vec2 position;
uniform mat4 transform;

void main() {
   gl_Position = transform * vec4(aPos.x + position.x, aPos.y + position.y, aPos.y, 1.0);
   vertexColor = color;
   texCoord = aTexCoord;
}