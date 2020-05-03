#version 450 core

out vec4 outColor;
in vec3 pos;

uniform vec4 color;

const float radius = 0.12;

vec3 position = (pos + 1) / 2.0;
float alpha = color.a - 0.9 * clamp(position.x, 0, color.a);

void colorEdges(float x, float y)
{
    const vec3 edgePosition = vec3(x, y, position.z) - position;

    if (length(edgePosition) < radius)
    {
        outColor = vec4(color.rgb, alpha);
    } else
    {
        outColor = vec4(0);
    }
}

void main()
{
    if (position.x < radius && position.y < radius)
    {
        colorEdges(radius, radius);
    } else if (position.x < radius && position.y > 1 - radius)
    {
        colorEdges(radius, 1 - radius);
    } else if (position.x > 1 - radius && position.y < radius)
    {
        colorEdges(1 - radius, radius);
    } else if (position.x > 1 - radius && position.y > 1 - radius)
    {
        colorEdges(1 - radius, 1 - radius);
    } else
    {
        outColor = vec4(color.rgb, alpha);
    }
}
