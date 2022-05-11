#version 450 core

in vec3 surfaceNormal;
in vec2 texCoordinates;
in vec3 worldPosition;

in vec3 lightPos;
in vec3 cameraPos;

uniform sampler2D objectTexture;
uniform vec3 lightColor;

out vec4 outColor;

uniform samplerCube skybox;
uniform float reflectiveFactor;
uniform float refractionFactor;
uniform float refractionIndex;

uniform int addShadow;

uniform float shineDamper;
uniform int material;

uniform int addBloom;
uniform sampler2D bloomTexture;
uniform float bloomStrength;

uniform vec4 color;

in vec4 fragmentPositionInLightSpace;
uniform sampler2D shadowMap;

uniform int useNormalMap;
uniform sampler2D normalMap;

float shadowCalculation(vec4 lightSpacePosition)
{
    vec3 clipSpace = lightSpacePosition.xyz / lightSpacePosition.w;
    clipSpace = clipSpace * 0.5 + 0.5;

    float closestDepth = texture(shadowMap, clipSpace.xy).r;
    float currentDepth = clipSpace.z;

    float bias = 0.005;
    float shadow = 0.0;
    vec2 texelSize = 1.0 / textureSize(shadowMap, 0);
    for (int x = -1; x <= 1; ++x)
    {
        for (int y = -1; y <= 1; ++y)
        {
            float pcfDepth = texture(shadowMap, clipSpace.xy + vec2(x, y) * texelSize).r;
            shadow += currentDepth - bias > pcfDepth ? 1.0 : 0.0;
        }
    }
    shadow /= 9.0;
    //    float shadow = currentDepth - bias > closestDepth ? 1.0 : 0.0;

    if (clipSpace.z > 1.0)
    {
        shadow = 0.0;
    }

    return shadow;
}

void main()
{
    vec3 normal;

    if (useNormalMap == 1)
    {
        normal = texture(normalMap, texCoordinates).rgb;
        normal = normalize(normal * 2.0 - 1.0);
    } else
    {
        normal = surfaceNormal;
    }
    
    vec4 textureColor = color + texture(objectTexture, texCoordinates);

    const float ambientFactor = 0.2;
    vec3 ambient = lightColor * ambientFactor;

    vec3 lightDirection = normalize(lightPos - worldPosition);

    float diffuseFactor = max(dot(lightDirection, normal), 0.0);
    vec3 diffuse = lightColor * diffuseFactor;

    float shadow = addShadow == 1 ? shadowCalculation(fragmentPositionInLightSpace) : 0;

    vec3 toCameraVector = normalize(cameraPos - worldPosition);
    vec3 reflectedVector = reflect(-lightDirection, normal);

    float specularFactor = max(dot(reflectedVector, toCameraVector), 0.0);
    specularFactor = pow(specularFactor, material);

    const float c0 = 1.0;
    const float c1 = 0.0;
    const float c2 = 0.001;

    float distance = length(lightPos - worldPosition);
    float attenuation = c0 + distance * c1 + distance * distance * c2;
    vec3 specular = specularFactor * shineDamper * lightColor / attenuation;

    vec3 totalColor = (diffuse * (1- shadow) + ambient) * textureColor.rgb + specular;

    vec3 R = reflect(toCameraVector, normal);
    vec3 reflectionColor = texture(skybox, R).rgb;
    outColor = vec4(mix(totalColor, reflectionColor, reflectiveFactor), 1.0);

    vec3 refractionVector = refract(toCameraVector, normal, refractionIndex);
    vec3 refractionColor = texture(skybox, refractionVector).rgb;

    outColor = vec4(mix(outColor.rgb, refractionColor, refractionFactor), 1.0);

    if (addBloom == 1)
    {
        outColor += texture(bloomTexture, texCoordinates) * bloomStrength;
    }
}
