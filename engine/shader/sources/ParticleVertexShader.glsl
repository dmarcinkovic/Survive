#version 450 core

layout (location = 0) in vec2 position;
layout (location = 1) in mat4 modelViewMatrix;
layout (location = 5) in vec4 texOffsets;
layout (location = 6) in float blendFactor;

out vec2 textureCoordinates1;
out vec2 textureCoordinates2;
out float blend;

uniform mat4 projectionMatrix;
uniform int numberOfRows;

void main()
{
    vec2 textureCoordinates = position + vec2(0.5, 0.5);

    textureCoordinates.y = 1.0 - textureCoordinates.y;
    textureCoordinates /= float(numberOfRows);

    textureCoordinates1 = textureCoordinates + texOffsets.xy;
    textureCoordinates2 = textureCoordinates * texOffsets.zw;

    blend = blendFactor;
    gl_Position = projectionMatrix * modelViewMatrix * vec4(position, 0.0, 1.0f);
}
