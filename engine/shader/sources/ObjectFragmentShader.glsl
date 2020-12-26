#version 450 core

in vec2 textCoords;
in vec3 surfaceNormal;
in vec3 worldPosition;

uniform sampler2D objectTexture;
uniform vec3 lightPosition;
uniform vec3 lightColor;
uniform vec3 cameraPosition;

uniform float shineDamper;
uniform int material;

out vec4 outColor;

in vec4 fragmentPositionInLightSpace;
uniform sampler2D shadowMap;

uniform samplerCube skybox;

float shadowCalculation(vec4 lightSpacePosition)
{
    vec3 clipSpace = lightSpacePosition.xyz / lightSpacePosition.w;
    clipSpace = clipSpace * 0.5 + 0.5;

    float closestDepth = texture(shadowMap, clipSpace.xy).r;
    float currentDepth = clipSpace.z;

    float bias = 0.005;
    float shadow = 0.0;
    vec2 texelSize = 1.0 / textureSize(shadowMap, 0);
    for(int x = -1; x <= 1; ++x)
    {
        for(int y = -1; y <= 1; ++y)
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
    vec4 textureColor = texture(objectTexture, textCoords);

    const float ambientFactor = 0.2;
    vec3 ambient = lightColor * ambientFactor;

    vec3 lightDirection = normalize(lightPosition - worldPosition);

    float diffuseFactor = max(dot(surfaceNormal, lightDirection), 0.0);
    vec3 diffuse = lightColor * diffuseFactor;

    float shadow = shadowCalculation(fragmentPositionInLightSpace);

    vec3 toCameraVector = normalize(cameraPosition - worldPosition);
    vec3 reflectedVector = reflect(-lightDirection, surfaceNormal);

    float specularFactor = max(dot(reflectedVector, toCameraVector), 0.0);
    specularFactor = pow(specularFactor, material);

    const float c0 = 1.0;
    const float c1 = 0.0;
    const float c2 = 0.001;

    float distance = length(lightPosition - worldPosition);
    float attenuation = c0 + distance * c1 + distance * distance * c2;
    vec3 specular = specularFactor * shineDamper * lightColor / attenuation;

    vec3 totalColor = (diffuse * (1- shadow) + ambient + specular) * textureColor.rgb;
    outColor = vec4(totalColor, 1.0);
}
