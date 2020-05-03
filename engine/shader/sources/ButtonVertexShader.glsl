#version 450 core

in vec3 position;
out vec3 pos;

uniform mat4 transformationMatrix;

void main()
{
    gl_Position = transformationMatrix * vec4(position, 1.0);

    pos = position;
}
