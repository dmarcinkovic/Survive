#version 450 core

layout (location = 0) in vec3 position;

uniform mat4 projectionMatrix;
uniform mat4 transformationMatrix;
uniform mat4 viewMatrix;

out vec2 textureCoords;

void main()
{
    gl_Position =  projectionMatrix * viewMatrix * transformationMatrix * vec4(position, 1.0);
    textureCoords = position.xy / 2.0 + vec2(0.5);
}
