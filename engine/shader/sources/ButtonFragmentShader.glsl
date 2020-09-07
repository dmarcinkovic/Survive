#version 450 core

out vec4 outColor;
in vec3 pos;

in vec2 textureCoordinates;

uniform vec4 color;
uniform bool isLoadingImage;

uniform sampler2D image;

void main()
{
    if (isLoadingImage)
    {
        outColor = texture(image, textureCoordinates);
    } else
    {
        outColor = color;
    }
}
