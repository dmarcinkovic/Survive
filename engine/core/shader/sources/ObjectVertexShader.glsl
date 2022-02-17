#version 450 core

layout (location = 0) in vec3 position;
layout (location = 1) in vec2 textureCoordinates;
layout (location = 2) in vec3 normal;
layout (location = 3) in vec3 tangent;

out vec3 surfaceNormal;

uniform mat4 transformationMatrix;
uniform mat4 projectionMatrix;
uniform mat4 viewMatrix;

out vec2 textCoords;
out vec3 worldPosition;

uniform mat4 lightProjectionMatrix;
uniform mat4 lightViewMatrix;
uniform vec4 plane;

uniform vec3 lightPosition;
uniform vec3 cameraPosition;

out vec4 fragmentPositionInLightSpace;

out vec3 lightPos;
out vec3 cameraPos;
out vec3 tangentFragPos;

void main()
{
    vec4 pos = transformationMatrix * vec4(position, 1.0);
    fragmentPositionInLightSpace = lightProjectionMatrix * lightViewMatrix * pos;

    gl_ClipDistance[0] = dot(pos, plane);

    gl_Position = projectionMatrix * viewMatrix * pos;
    textCoords = textureCoordinates;

    mat3 normalMatrix = transpose(inverse(mat3(transformationMatrix)));
    vec3 T = normalize(normalMatrix * tangent);
    vec3 N = normalize(normalMatrix * normal);
    vec3 B = cross(N, T);

    surfaceNormal = normalMatrix * normal;
    surfaceNormal = normalize(surfaceNormal);
    worldPosition = pos.xyz;

    mat3 TBN = transpose(mat3(T, B, N));
    lightPos = TBN * lightPosition;
    cameraPos = TBN * cameraPosition;
    tangentFragPos = TBN * worldPosition;
}
