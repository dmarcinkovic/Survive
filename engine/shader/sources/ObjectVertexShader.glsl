#version 450 core

in vec3 position;
in vec3 normal;
in vec2 textureCoordinates;

out vec2 textCoords;

void main()
{
    gl_Position =vec4(position, 1.0);
    textCoords = textureCoordinates;
}
