#version 450 core

out vec4 outColor;

in vec2 textCoords;
uniform sampler2D image;

void main()
{
    outColor = texture(image, textCoords);
}
