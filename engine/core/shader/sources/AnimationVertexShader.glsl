#version 450 core

layout (location = 0) in vec3 position;
layout (location = 1) in vec2 textures;
layout (location = 2) in vec3 normal;
layout (location = 3) in vec3 jointWeight;
layout (location = 4) in ivec3 jointID;
layout (location = 5) in vec3 tangent;

const int MAX_JOINTS = 50;
const int MAX_WEIGHTS = 3;

uniform mat4 transformationMatrix;
uniform mat4 viewMatrix;
uniform mat4 projectionMatrix;

uniform mat4 jointTransforms[MAX_JOINTS];
uniform vec4 plane;

out vec3 surfaceNormal;
out vec2 texCoordinates;
out vec3 worldPosition;

uniform mat4 lightProjectionMatrix;
uniform mat4 lightViewMatrix;

uniform int useNormalMap;
uniform vec3 cameraPosition;
uniform vec3 lightPosition;

out vec4 fragmentPositionInLightSpace;
out vec3 lightPos;
out vec3 cameraPos;

void main()
{
    vec4 worldPos = transformationMatrix * vec4(position, 1.0);
    fragmentPositionInLightSpace = lightProjectionMatrix * lightViewMatrix * worldPos;

    gl_ClipDistance[0] = dot(worldPos, plane);

    vec4 totalLocalPos = vec4(position, 1.0);
    vec4 totalNormal = vec4(0.0);

    for (int i = 0; i < MAX_WEIGHTS; ++i)
    {
        if (jointID[i] == -1)
        {
            break;
        }

        mat4 jointTransform = jointTransforms[jointID[i]];
        vec4 pose = jointTransform * vec4(position, 1.0);
        totalLocalPos += pose * jointWeight[i];

        vec4 worldNormal = jointTransform * vec4(normal, 0.0);
        totalNormal += worldNormal * jointWeight[i];
    }

    gl_Position = projectionMatrix * viewMatrix * transformationMatrix * totalLocalPos;

    mat3 normalMatrix = transpose(inverse(mat3(transformationMatrix)));

    worldPosition = worldPos.xyz;
    texCoordinates = textures;

    if (useNormalMap == 1)
    {
        vec3 T = normalize(normalMatrix * tangent);
        vec3 N = normalize(normalMatrix * normal);
        vec3 B = cross(N, T);

        mat3 TBN = transpose(mat3(T, B, N));
        lightPos = TBN * lightPosition;
        cameraPos = TBN * cameraPosition;
        worldPosition = TBN * worldPosition;
    } else
    {
        surfaceNormal = normalMatrix * normal;
        surfaceNormal = normalize(surfaceNormal);

        cameraPos = cameraPosition;
        lightPos = lightPosition;
    }
}
