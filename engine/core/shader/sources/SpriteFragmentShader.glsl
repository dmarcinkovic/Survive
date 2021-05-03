#version 450 core

in vec2 textureCoords;

uniform sampler2D image;

out vec4 outColor;

void main()
{
    outColor = texture(image, textureCoords);;
}
