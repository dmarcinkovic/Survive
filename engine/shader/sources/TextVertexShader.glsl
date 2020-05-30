#version 450 core

in vec2 position;
in vec2 texCoords;

uniform mat4 transformationMatrix;

out vec2 textureCoords;

void main()
{
    gl_Position = transformationMatrix * vec4(position, 0.0, 1.0);
    textureCoords = texCoords;
}
