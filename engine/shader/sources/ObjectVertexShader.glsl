#version 450 core

in vec3 position;
in vec2 textureCoordinates;
in vec3 normal;

out vec3 surfaceNormal;

uniform mat4 transformationMatrix;
uniform mat4 projectionMatrix;
uniform mat4 viewMatrix;

out vec2 textCoords;

void main()
{
    gl_Position = projectionMatrix * viewMatrix * transformationMatrix * vec4(position, 1.0);
    textCoords = textureCoordinates;

    surfaceNormal = mat3(transpose(inverse(transformationMatrix))) * normal;
    surfaceNormal = normalize(surfaceNormal);
}
