#version 450 core

in vec2 textCoords;
in vec3 surfaceNormal;

uniform sampler2D objectTexture;

out vec4 outColor;

void main()
{
    outColor = vec4(texture(objectTexture, textCoords));
}
