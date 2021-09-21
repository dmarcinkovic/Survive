#version 450 core

layout (location = 0) in vec3 position;
layout (location = 3) in vec3 jointWeight;
layout (location = 4) in ivec3 jointID;

const int MAX_JOINTS = 50;
const int MAX_WEIGHTS = 3;

uniform mat4 jointTransforms[MAX_JOINTS];
uniform int loadAnimatedModel;

uniform mat4 transformationMatrix;
uniform mat4 projectionMatrix;
uniform mat4 viewMatrix;

void main()
{
    vec4 totalLocalPos = vec4(position, 1.0);

    for (int i = 0; loadAnimatedModel == 1 && i < MAX_WEIGHTS; ++i)
    {
        if (jointID[i] == -1)
        {
            break;
        }

        mat4 jointTransform = jointTransforms[jointID[i]];
        vec4 pose = jointTransform * vec4(position, 1.0);
        totalLocalPos += pose * jointWeight[i];
    }

    gl_Position = projectionMatrix * viewMatrix * transformationMatrix * totalLocalPos;
}
