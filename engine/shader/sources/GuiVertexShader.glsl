#version 450 core

layout (location = 0) in vec2 position;

out vec2 textureCoords;

uniform mat4 transformationMatrix;
uniform mat4 projectionMatrix;

void main()
{
    gl_Position = projectionMatrix * transformationMatrix * vec4(position, 0.0, 1.0);
    textureCoords = position / 2.0 + vec2(0.5);
}
