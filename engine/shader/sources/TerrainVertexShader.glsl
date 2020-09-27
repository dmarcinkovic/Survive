#version 450 core

layout (location = 0) in vec3 position;

uniform mat4 projectionMatrix;
uniform mat4 transformationMatrix;
uniform mat4 viewMatrix;

uniform mat4 lightProjectionMatrix;
uniform mat4 lightViewMatrix;

out vec4 fragmentPositionInLightSpace;
out vec2 textureCoords;

void main()
{
    const mat4 lightSpaceMatrix = lightProjectionMatrix * lightViewMatrix;
    vec4 worldPosition = transformationMatrix * vec4(position, 1.0);
    fragmentPositionInLightSpace = lightSpaceMatrix * worldPosition;

    gl_Position =  projectionMatrix * viewMatrix * worldPosition;
    textureCoords = position.xy / 2.0 + vec2(0.5);
}
