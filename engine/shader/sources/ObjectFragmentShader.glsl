#version 450 core

in vec2 textCoords;
in vec3 surfaceNormal;
in vec3 worldPosition;

uniform sampler2D objectTexture;
uniform vec3 lightPosition;
uniform vec3 lightColor;

out vec4 outColor;

in vec4 fragmentPositionInLightSpace;
uniform sampler2D shadowMap;

float shadowCalculation(vec4 lightSpacePosition,vec3 lightDirection)
{
    vec3 clipSpace = lightSpacePosition.xyz / lightSpacePosition.w;
    clipSpace = clipSpace * 0.5 + 0.5;

    float closestDepth = texture(shadowMap, clipSpace.xy).r;
    float currentDepth = clipSpace.z;

    float bias = 0.005;
    float shadow = currentDepth - bias > closestDepth ? 1.0 : 0.0;

    if (clipSpace.z > 1.0)
    {
        shadow = 0.0;
    }

    return shadow;
}

void main()
{
    vec3 lightPos = normalize(lightPosition);
    vec4 textureColor = texture(objectTexture, textCoords);

    const float ambientFactor = 0.2;
    vec3 ambient = lightColor * ambientFactor;

    vec3 lightDirection = normalize(lightPos - worldPosition);

    float diffuseFactor = max(dot(surfaceNormal, lightPos), 0.0);
    vec3 diffuse = lightColor * diffuseFactor;

    float shadow = shadowCalculation(fragmentPositionInLightSpace, lightPos);

    vec3 totalColor = (ambient + (1 - shadow) * diffuse) * textureColor.rgb;

    outColor = vec4(totalColor, 1.0);
}
