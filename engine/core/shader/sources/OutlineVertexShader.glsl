#version 450 core

layout (location = 0) in vec3 position;
layout (location = 2) in vec3 normal;

uniform mat4 transformationMatrix;
uniform mat4 viewMatrix;
uniform mat4 projectionMatrix;

void main()
{
    vec3 unitNormal = normalize(normal);
    gl_Position = projectionMatrix * viewMatrix * transformationMatrix * vec4(position + unitNormal * 0.1, 1.0);
}
