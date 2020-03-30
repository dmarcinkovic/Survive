#version 450 core

uniform sampler2D textureAtlas;

in vec2 textureCoords;
out vec4 outColor;

uniform vec3 color;

void main()
{
    outColor = vec4(color, texture(textureAtlas, textureCoords).a);
}
