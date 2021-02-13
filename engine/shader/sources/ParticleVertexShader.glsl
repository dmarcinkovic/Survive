#version 450 core

layout (location = 0) in vec3 position;
layout (location = 1) mat4 modelViewMatrix;
layout (location = 5) float blendFactor;
layout (location = 6) vec4 texOffsets;

out vec2 textureCoordinates1;
out vec2 textureCoordinates2;
out float blend;

uniform mat4 projectionMatrix;
uniform int numberOfRows;

void main() {
    vec2 textureCoordinates = position.xy + vec2(0.5, 0.5);

    textureCoordinates.y = 1.0 - textureCoordinates.y;
    textureCoordinates /= float(numberOfRows);

    textureCoordinates1 = textureCoordinates + texOffsets.xy;
    textureCoordinates2 = textureCoordinates * texOffsets.zw;

    blend = blendFactor;
    gl_Position = projectionMatrix * modelViewMatrix * vec4(position, 1.0f);
}
