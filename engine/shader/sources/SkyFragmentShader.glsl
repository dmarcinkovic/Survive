#version 450 core

out vec4 outColor;

in vec3 textureCoordinates;
uniform samplerCube skybox;

void main()
{
    outColor = texture(skybox, textureCoordinates);
}
