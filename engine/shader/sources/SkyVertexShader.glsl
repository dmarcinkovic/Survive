#version 450 core

layout (location = 0) in vec3 position;

out vec3 textureCoordinates;

uniform mat4 viewMatrix;
uniform mat4 projectionMatrix;
uniform mat4 transformationMatrix;
uniform vec4 plane;

void main()
{
    textureCoordinates = position;

    vec4 pos = transformationMatrix * vec4(position, 1.0);
    gl_ClipDistance[0] = dot(pos, plane);

    gl_Position = projectionMatrix * viewMatrix * pos;
}
