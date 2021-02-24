#version 450 core

in vec2 textureCoordinates;
in vec4 clipSpace;
in vec3 toCameraVector;

out vec4 outColor;

uniform sampler2D reflectionTexture;
uniform sampler2D refractionTexture;
uniform sampler2D duDvMap;
uniform sampler2D normalMap;
uniform float moveFactor;

const float waveStrength = 0.03;

vec2 calculateDistortedCoordinates()
{
    vec2 distortedTextureCoordinates = texture(duDvMap, vec2(textureCoordinates.x + moveFactor,
                                            textureCoordinates.y)).rg * 0.1;

    distortedTextureCoordinates = textureCoordinates + vec2(distortedTextureCoordinates.x,
                                        distortedTextureCoordinates.y + moveFactor);

    return distortedTextureCoordinates;
}

vec2 calculateDistortion(vec2 distortedTextureCoordinates)
{
    return (texture(duDvMap, distortedTextureCoordinates).rg * 2.0 - 1.0) * waveStrength;
}

void main()
{
    vec2 normalizedDeviceCoordinates = (clipSpace.xy / clipSpace.w) / 2.0 + 0.5;

    vec2 distortedTextureCoordinates = calculateDistortedCoordinates();
    vec2 totalDistortion = calculateDistortion(distortedTextureCoordinates);

    vec2 refractionTextureCoordinates = normalizedDeviceCoordinates + totalDistortion;
    vec2 reflectionTextureCoordinates = vec2(normalizedDeviceCoordinates.x, -normalizedDeviceCoordinates.y) + totalDistortion;

    refractionTextureCoordinates = clamp(refractionTextureCoordinates, 0.001, 0.999);

    reflectionTextureCoordinates.x = clamp(reflectionTextureCoordinates.x, 0.001, 0.999);
    reflectionTextureCoordinates.y = clamp(reflectionTextureCoordinates.y, -0.999, -0.001);

    vec4 reflectionColor = texture(reflectionTexture, reflectionTextureCoordinates);
    vec4 refractionColor = texture(refractionTexture, refractionTextureCoordinates);

    vec3 viewVector = normalize(toCameraVector);
    float refractiveFactor = dot(viewVector, vec3(0, 1, 0));

    vec4 normalMapColor = texture(normalMap, distortedTextureCoordinates);;
    vec3 normal = vec3(normalMapColor.r * 2.0 - 1.0, normalMapColor.b, normalMapColor.g * 2.0 - 1.0);
    normal = normalize(normal); 

    outColor = mix(reflectionColor, refractionColor, refractiveFactor);
    outColor = mix(outColor, vec4(0.0, 0.3, 0.5, 1.0), 0.2);
}
