#version 450 core

in vec3 position;
in vec3 normal;
in vec2 textureCoordinates;

uniform mat4 transformationMatrix;
uniform mat4 projectionMatrix;
uniform mat4 viewMatrix;

out vec2 textCoords;

void main()
{
    gl_Position = projectionMatrix * viewMatrix * transformationMatrix * vec4(position, 1.0);
    textCoords = textureCoordinates;
}
