#version 450 core

layout (location = 0) in vec3 position;
layout (location = 1) in vec2 textureCoordinates;
layout (location = 2) in vec3 normal;

out vec3 surfaceNormal;

uniform mat4 transformationMatrix;
uniform mat4 projectionMatrix;
uniform mat4 viewMatrix;

out vec2 textCoords;
out vec3 worldPosition;

uniform mat4 lightProjectionMatrix;
uniform mat4 lightViewMatrix;
uniform vec4 plane;

out vec4 fragmentPositionInLightSpace;

void main()
{
    vec4 pos = transformationMatrix * vec4(position, 1.0);
    fragmentPositionInLightSpace = lightProjectionMatrix * lightViewMatrix * pos;

    gl_ClipDistance[0] = dot(pos, plane);

    gl_Position = projectionMatrix * viewMatrix * pos;
    textCoords = textureCoordinates;

    surfaceNormal = mat3(transpose(inverse(transformationMatrix))) * normal;
    surfaceNormal = normalize(surfaceNormal);
    worldPosition = pos.xyz;
}
