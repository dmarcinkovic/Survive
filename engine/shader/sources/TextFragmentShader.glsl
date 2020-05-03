#version 450 core

uniform sampler2D textureAtlas;
uniform vec3 borderColor;
uniform float borderWidth;

in vec2 textureCoords;
out vec4 outColor;

uniform vec3 color;

const float width = 0.5f;
const float edge = 0.05f;

const float borderEdge = 0.1;

void main()
{
    float distance = 1.0f - texture(textureAtlas, textureCoords).a;

    float alpha = 1.0f - smoothstep(width, width + edge, distance);
    float borderAlpha = 1.0f - smoothstep(borderWidth, borderWidth + borderEdge, distance);

    float totalAlpha = alpha + (1.0 - alpha) * borderAlpha;
    vec3 totalColor = mix(borderColor, color, alpha / totalAlpha);

    outColor = vec4(totalColor, totalAlpha);
}
