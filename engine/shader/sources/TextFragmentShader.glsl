#version 450 core

uniform sampler2D textureAtlas;

in vec2 textureCoords;
out vec4 outColor;

uniform vec3 color;

const float width = 0.5f;
const float edge = 0.1f;

void main()
{
    float distance = 1.0f - texture(textureAtlas, textureCoords).a;

    float alpha = 1.0f - smoothstep(width, width + edge, distance);

    outColor = vec4(color, alpha);
}
