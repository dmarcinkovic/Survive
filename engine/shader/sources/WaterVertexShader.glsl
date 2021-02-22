#version 450 core

layout (location = 0) in vec2 position;

out vec2 textureCoordinates;

uniform mat4 projectionMatrix;
uniform mat4 viewMatrix;
uniform mat4 transformationMatrix;

void main()
{
    gl_Position = projectionMatrix * viewMatrix * transformationMatrix * vec4(position.x, 0.0, position.y, 1.0);
    textureCoordinates = vec2(position.x / 2.0 + 0.5, position.y / 2.0 + 0.5);
}
