#version 450 core

in vec2 textureCoordinates;
in vec4 clipSpace;
in vec3 toCameraVector;
in vec3 fromLightVector;

out vec4 outColor;

uniform sampler2D reflectionTexture;
uniform sampler2D refractionTexture;
uniform sampler2D duDvMap;
uniform sampler2D normalMap;
uniform float moveFactor;
uniform vec3 lightColor;
uniform sampler2D depthMap;

const float waveStrength = 0.03f;
const float shineDamper = 20.0f;
const float reflectivity = 0.6f;

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

    float near = 0.1;
    float far = 1000.0f;
    float depth = texture(depthMap, normalizedDeviceCoordinates).r;
    float floorDistance = 2.0 * near * far / (far + near - (2.0 * depth - 1.0) * (far - near));
    float waterDistance = 2.0 * near * far / (far + near - (2.0 * gl_FragCoord.z - 1.0) * (far - near));
    float waterDepth = floorDistance - waterDistance;

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

    vec3 reflectedLight = reflect(normalize(fromLightVector), normal);
    float specular = max(dot(reflectedLight, viewVector), 0.0);
    specular = pow(specular, shineDamper);
    vec3 specularHighlights = lightColor * specular * reflectivity;

    outColor = mix(reflectionColor, refractionColor, refractiveFactor);
    outColor = mix(outColor, vec4(0.0, 0.3, 0.5, 1.0), 0.2) + vec4(specularHighlights, 0.0);
    outColor.a = clamp(waterDepth / 5.0, 0, 1);
}
