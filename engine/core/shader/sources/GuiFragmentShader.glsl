#version 450 core

in vec2 textureCoords;

out vec4 outColor;

uniform sampler2D image;
uniform vec4 color;

void main()
{
    outColor = color + texture(image, textureCoords);
}
