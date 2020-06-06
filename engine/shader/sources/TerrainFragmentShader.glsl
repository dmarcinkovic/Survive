#version 450 core

out vec4 outColor;

uniform sampler2D shadowMap;

in vec4 fragmentPositionInLightSpace;

float shadowCalculation(vec4 lightSpacePosition)
{
    vec3 clipSpace = lightSpacePosition.xyz / lightSpacePosition.w;
    clipSpace = clipSpace * 0.5 + 0.5;

    float closestDepth = texture(shadowMap, clipSpace.xy).r;
    float currentDepth = clipSpace.z;

    float shadow = 0.0;
    vec2 texelSize = 1.0 / textureSize(shadowMap, 0);
    for(int x = -1; x <= 1; ++x)
    {
        for(int y = -1; y <= 1; ++y)
        {
            float pcfDepth = texture(shadowMap, clipSpace.xy + vec2(x, y) * texelSize).r;
            shadow += currentDepth > pcfDepth ? 1.0 : 0.0;
        }
    }
    shadow /= 9.0;

    if (clipSpace.z > 1.0)
    {
        shadow = 0.0;
    }

    return shadow;
}

void main()
{
    float shadow = shadowCalculation(fragmentPositionInLightSpace);
    const vec3 color = (1 - shadow) * vec3(0.6);
    outColor = vec4(color, 1.0);
}
