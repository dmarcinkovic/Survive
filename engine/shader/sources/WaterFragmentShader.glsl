#version 450 core

in vec2 textureCoordinates;
in vec4 clipSpace;

out vec4 outColor;

uniform sampler2D reflectionTexture;
uniform sampler2D refractionTexture;
uniform sampler2D duDvMap;
uniform sampler2D normalMap;
uniform float moveFactor;

const float waveStrength = 0.03;

vec2 calculateDistortion()
{
    vec2 distortion1 = (texture(duDvMap, vec2(textureCoordinates.x + moveFactor,
    textureCoordinates.y)).rg * 2.0f - 1.0f) * waveStrength;

    vec2 distortion2 = (texture(duDvMap, vec2(-textureCoordinates.x + moveFactor,
    textureCoordinates.y + moveFactor)).rg * 2.0f - 1.0f) * waveStrength;

    return distortion1 + distortion2;
}

void main()
{
    vec2 normalizedDeviceCoordinates = (clipSpace.xy / clipSpace.w) / 2.0 + 0.5;
    vec2 totalDistortion = calculateDistortion();

    vec2 refractionTextureCoordinates = normalizedDeviceCoordinates + totalDistortion;
    vec2 reflectionTextureCoordinates = vec2(normalizedDeviceCoordinates.x, -normalizedDeviceCoordinates.y) + totalDistortion;

    refractionTextureCoordinates = clamp(refractionTextureCoordinates, 0.001, 0.999);

    reflectionTextureCoordinates.x = clamp(reflectionTextureCoordinates.x, 0.001, 0.999);
    reflectionTextureCoordinates.y = clamp(reflectionTextureCoordinates.y, -0.999, -0.001);

    vec4 reflectionColor = texture(reflectionTexture, reflectionTextureCoordinates);
    vec4 refractionColor = texture(refractionTexture, refractionTextureCoordinates);

    outColor = mix(reflectionColor, refractionColor, 0.5);
    outColor = mix(outColor, vec4(0.0, 0.3, 0.5, 1.0), 0.2);
}
