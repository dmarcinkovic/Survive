#version 450 core

out vec4 outColor;

in vec2 textureCoordinates;

uniform sampler2D particleTexture;
uniform vec4 color;

void main()
{
    vec4 textureColor = texture(particleTexture, textureCoordinates);

    outColor = color + textureColor;
}
