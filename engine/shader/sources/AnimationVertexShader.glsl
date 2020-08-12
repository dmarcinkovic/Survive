#version 450 core

in vec3 position;
in vec3 normal;
in vec2 textures;
in ivec3 jointID;
in vec3 jointWeigth;

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
