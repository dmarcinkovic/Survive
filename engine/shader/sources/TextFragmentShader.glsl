#version 450 core

uniform sampler2D textureAtlas;

in vec2 textureCoords;
out vec4 outColor;

void main()
{
    outColor = vec4(1.0, 0.0, 0.0, texture(textureAtlas, textureCoords).a);
}
