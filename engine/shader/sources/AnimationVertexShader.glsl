#version 450 core

layout (location = 0) in vec3 position;
layout (location = 1) in vec2 textures;
layout (location = 2) in vec3 normal;
layout (location = 3) in vec3 jointWeigth;
layout (location = 4) in ivec3 jointID;

const int MAX_JOINTS = 50;
const int MAX_WEIGHTS = 3;

uniform mat4 transformationMatrix;
uniform mat4 viewMatrix;
uniform mat4 projectionMatrix;

uniform mat4 jointTransforms[MAX_JOINTS];

out vec3 surfaceNormal;
out vec2 texCoordinates;
out vec3 worldPosition;

void main()
{
    vec4 worldPos = transformationMatrix * vec4(position, 1.0);

    vec4 totalLocalPos = vec4(0.0);
    vec4 totalNormal = vec4(0.0);

    for (int i = 0; i < MAX_WEIGHTS; ++i)
    {
        if (jointID[i] == -1)
        {
            break;
        }

        mat4 jointTransform = jointTransforms[jointID[i]];
        vec4 pose = jointTransform * vec4(position, 1.0);
        totalLocalPos += pose * jointWeigth[i];
    }

    gl_Position = projectionMatrix * viewMatrix * worldPos;

    worldPosition = worldPos.xyz;
    texCoordinates = textures;
    surfaceNormal = mat3(inverse(transpose(transformationMatrix))) * normal;
    surfaceNormal = normalize(surfaceNormal);
}
