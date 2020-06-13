#version 450 core

out vec4 outColor;

uniform sampler2D blendMap;
uniform sampler2D grass;
uniform sampler2D dirt;
uniform sampler2D rock;

void main()
{
    outColor = vec4(vec3(0.5), 1.0);
}
