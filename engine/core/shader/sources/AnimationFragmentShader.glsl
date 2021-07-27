#version 450 core

in vec3 surfaceNormal;
in vec2 texCoordinates;
in vec3 worldPosition;

uniform sampler2D objectTexture;
uniform vec3 lightPosition;
uniform vec3 lightColor;
uniform vec3 cameraPosition;

out vec4 outColor;

uniform samplerCube skybox;
uniform float reflectiveFactor;
uniform float refractionFactor;
uniform float refractionIndex;

uniform int addShadow;

uniform int addBloom;
uniform sampler2D bloomTexture;
uniform float bloomStrength;

uniform vec4 color;
uniform int renderColor;

in vec4 fragmentPositionInLightSpace;
uniform sampler2D shadowMap;

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
    vec4 textureColor = texture(objectTexture, texCoordinates);

    const float ambientFactor = 0.2;
    vec3 ambient = lightColor * ambientFactor;

    vec3 lightDirection = normalize(lightPosition - worldPosition);
    const float diffuseFactor = max(dot(lightDirection, surfaceNormal), 0.0);
    vec3 diffuse = lightColor * diffuseFactor;

    vec3 totalColor = (diffuse + ambient) * textureColor.rgb;

    outColor = vec4(totalColor, 1.0);
}
