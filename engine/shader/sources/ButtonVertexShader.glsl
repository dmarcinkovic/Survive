#version 450 core

in vec3 position;
out vec3 pos;

uniform mat4 transformationMatrix;

out vec2 textureCoordinates;

void main()
{
    gl_Position = transformationMatrix * vec4(position, 1.0);
    pos = position;
    textureCoordinates = position.xy / 2.0 + vec2(0.5);;
}
