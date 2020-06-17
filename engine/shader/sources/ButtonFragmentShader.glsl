#version 450 core

out vec4 outColor;
in vec3 pos;

uniform vec4 color;
//uniform bool loadImage;
//
//uniform sampler2D image;

void main()
{
    outColor = color;
}
