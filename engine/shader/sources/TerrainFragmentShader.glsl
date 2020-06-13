#version 450 core

out vec4 outColor;

uniform sampler2D blendMap;
uniform sampler2D grass;
uniform sampler2D dirt;
uniform sampler2D rock;
uniform sampler2D flowers;

in vec2 textureCoords;

const float scaleFactor = 40;

void main()
{
    vec2 coordinate = textureCoords * scaleFactor;
    vec4 blendColor = texture(blendMap, textureCoords);

    float backTexture = 1 - (blendColor.r + blendColor.g + blendColor.b);

    vec4 color1 = texture(dirt, coordinate) * blendColor.r;
    vec4 color2 = texture(flowers, coordinate) * blendColor.g;
    vec4 color3 = texture(rock, coordinate) * blendColor.b;
    vec4 color4 = texture(grass, coordinate) * backTexture;

    vec4 totalColor = color1 + color2 + color3 + color4;

    outColor = totalColor;
}
