#version 450 core

out vec4 outColor;

in vec2 textureCoordinates1;
in vec2 textureCoordinates2;
in float blend;

uniform sampler2D particleTexture;

void main()
{
    vec4 color1 = texture(particleTexture, textureCoordinates1);
    vec4 color2 = texture(particleTexture, textureCoordinates2);

    outColor = mix(color1, color2, blend);
}
