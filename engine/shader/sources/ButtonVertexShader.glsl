#version 450 core

layout (location = 0) in vec3 position;

uniform mat4 transformationMatrix;

out vec3 pos;
out vec2 textureCoordinates;

void main()
{
    gl_Position = transformationMatrix * vec4(position, 1.0);
    pos = position;
    textureCoordinates = position.xy / 2.0 + vec2(0.5);;
}
