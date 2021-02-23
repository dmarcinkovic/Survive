#version 450 core

in vec2 textureCoordinates;
in vec4 clipSpace;

out vec4 outColor;

uniform sampler2D reflectionTexture;
uniform sampler2D refractionTexture;

void main()
{
    vec2 normalizedDeviceCoordinates = (clipSpace.xy / clipSpace.w) / 2.0 + 0.5;
    vec2 refractionTextureCoordinates = normalizedDeviceCoordinates;
    vec2 reflectionTextureCoordinates = vec2(normalizedDeviceCoordinates.x, -normalizedDeviceCoordinates.y);

    vec4 reflectionColor = texture(reflectionTexture, reflectionTextureCoordinates);
    vec4 refractionColor = texture(refractionTexture, refractionTextureCoordinates);

    outColor = mix(reflectionColor, refractionColor, 0.5);
}
