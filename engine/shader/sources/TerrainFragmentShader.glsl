#version 450 core

out vec4 outColor;

//uniform sampler2D shadowMap;

in vec4 fragmentPositionInLightSpace;

uniform sampler2D blendMap;
uniform sampler2D grass;
uniform sampler2D dirt;
uniform sampler2D rock;
uniform sampler2D flowers;

in vec2 textureCoords;

const float scaleFactor = 40;

float shadowCalculation(vec4 lightSpacePosition)
{
    vec3 clipSpace = lightSpacePosition.xyz / lightSpacePosition.w;
    clipSpace = clipSpace * 0.5 + 0.5;

//    float closestDepth = texture(shadowMap, clipSpace.xy).r;
    float currentDepth = clipSpace.z;

    float shadow = 0.0;
//    vec2 texelSize = 1.0 / textureSize(shadowMap, 0);
    for (int x = -1; x <= 1; ++x)
    {
        for (int y = -1; y <= 1; ++y)
        {
//            float pcfDepth = texture(shadowMap, clipSpace.xy + vec2(x, y) * texelSize).r;
//            shadow += currentDepth > pcfDepth ? 1.0 : 0.0;
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
//    float shadow = shadowCalculation(fragmentPositionInLightSpace);

    vec2 coordinate = textureCoords * scaleFactor;
    vec4 blendColor = texture(blendMap, textureCoords);

    float backTexture = 1 - (blendColor.r + blendColor.g + blendColor.b);

    const vec4 shade = vec4(vec3(0.6), 1.0);

    vec4 color1 = (texture(dirt, coordinate) * blendColor.r) ;
    vec4 color2 = ( texture(flowers, coordinate) * blendColor.g) ;
    vec4 color3 = ( texture(rock, coordinate) * blendColor.b) ;
    vec4 color4 = ( texture(grass, coordinate) * backTexture) ;

    outColor = color1 + color2 + color3 + color4;
}
