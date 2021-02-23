#version 450 core

in vec2 textureCoordinates;

out vec4 outColor;

uniform sampler2D reflectionTexture;
uniform sampler2D refractionTexture;

void main()
{
    vec4 reflectionColor = texture(reflectionTexture, textureCoordinates);
    vec4 refractionColor = texture(refractionTexture, textureCoordinates);

    outColor = mix(reflectionColor, refractionColor, 0.5);
}
