#version 450 core

out vec4 outColor;

uniform sampler2D blendMap;
uniform sampler2D grass;
uniform sampler2D dirt;
uniform sampler2D rock;

in vec2 textureCoords;

void main()
{
    outColor = texture(rock, textureCoords);
}
