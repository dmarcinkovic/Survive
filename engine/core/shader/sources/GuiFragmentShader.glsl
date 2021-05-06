#version 450 core

in vec2 textureCoords;

out vec4 outColor;

uniform sampler2D image;

void main()
{
    outColor = texture(image, textureCoords);
}
