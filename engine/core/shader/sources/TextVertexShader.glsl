#version 450 core

layout (location = 0) in vec2 position;
layout (location = 1) in vec2 texCoords;

uniform mat4 transformationMatrix;
uniform mat4 projectionMatrix;

out vec2 textureCoords;

void main()
{
    gl_Position = projectionMatrix * transformationMatrix * vec4(position, 0.0, 1.0);
    textureCoords = texCoords;
}
