#version 450 core

out vec4 outColor;
in vec3 pos;

uniform vec4 color;

void main()
{
    outColor = color;
}
