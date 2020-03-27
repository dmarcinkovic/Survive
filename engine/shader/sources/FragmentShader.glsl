#version 450 core

out vec4 outColor;

uniform sampler2D image;
in vec2 textureCoords;

void main()
{
    outColor = texture(image, textureCoords);
}
