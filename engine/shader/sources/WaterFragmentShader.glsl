#version 450 core

in vec2 textureCoordinates;
in vec4 clipSpace;

out vec4 outColor;

uniform sampler2D reflectionTexture;
uniform sampler2D refractionTexture;
uniform sampler2D duDvMap;
uniform sampler2D normalMap;

void main()
{
    vec2 normalizedDeviceCoordinates = (clipSpace.xy / clipSpace.w) / 2.0 + 0.5;
    vec2 refractionTextureCoordinates = normalizedDeviceCoordinates;
    vec2 reflectionTextureCoordinates = vec2(normalizedDeviceCoordinates.x, -normalizedDeviceCoordinates.y);

    vec2 distortion1 = texture(duDvMap, vec2(textureCoordinates.x, textureCoordinates.y)).rg * 2.0f - 1.0f;

    vec4 reflectionColor = texture(reflectionTexture, reflectionTextureCoordinates);
    vec4 refractionColor = texture(refractionTexture, refractionTextureCoordinates);

    outColor = mix(reflectionColor, refractionColor, 0.5);
}
