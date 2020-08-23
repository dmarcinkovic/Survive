#version 450 core

layout (location = 0) in vec3 position;
layout (location = 1) in vec2 textures;
layout (location = 2) in vec3 normal;
layout (location = 3) in vec3 jointWeigth;
layout (location = 4) in ivec3 jointID;

uniform mat4 transformationMatrix;
uniform mat4 viewMatrix;
uniform mat4 projectionMatrix;

out vec3 surfaceNormal;
out vec2 texCoordinates;
out vec3 worldPosition;

void main()
{
    vec4 worldPos = transformationMatrix * vec4(position, 1.0);
    gl_Position = projectionMatrix * viewMatrix * worldPos;

    worldPosition = worldPos.xyz;
    texCoordinates = textures;
    surfaceNormal = mat3(inverse(transpose(transformationMatrix))) * normal;
    surfaceNormal = normalize(surfaceNormal);
}
