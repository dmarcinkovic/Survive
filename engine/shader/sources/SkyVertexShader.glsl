#version 450 core

layout (location = 0) in vec3 position;

out vec3 textureCoordinates;

uniform mat4 viewMatrix;
uniform mat4 projectionMatrix;

void main()
{
    textureCoordinates = position;
    vec4 pos = projectionMatrix * viewMatrix * vec4(position, 1.0);
    gl_Position = pos.xyww;
}
