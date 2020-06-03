#version 450 core

in vec3 position;

uniform mat4 projectionMatrix;
uniform mat4 transformationMatrix;
uniform mat4 viewMatrix;
uniform mat4 lightSpaceMatrix;

out vec4 fragmentPositionInLightSpace;

void main()
{
    vec4 worldPosition = transformationMatrix * vec4(position, 1.0);
    fragmentPositionInLightSpace = lightSpaceMatrix * worldPosition;

    gl_Position =  projectionMatrix * viewMatrix * worldPosition;
}
