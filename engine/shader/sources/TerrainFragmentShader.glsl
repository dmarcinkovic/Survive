#version 450 core

out vec4 outColor;

uniform sampler2D shadowMap;

in vec4 fragmentPositionInLightSpace;

float shadowCalculation(vec4 lightSpacePosition)
{
    vec3 projCoords = lightSpacePosition.xyz / lightSpacePosition.w;
    projCoords = projCoords * 0.5 + 0.5;

    float closestDepth = texture(shadowMap, projCoords.xy).r;
    float currentDepth = projCoords.z;

    float shadow = currentDepth > closestDepth ? 1.0 : 0.0;

    return shadow;
}

void main()
{
    float shadow = shadowCalculation(fragmentPositionInLightSpace);
    const vec3 color = (1 - shadow) * vec3(0.6);
    outColor = vec4(color, 1.0);
}
