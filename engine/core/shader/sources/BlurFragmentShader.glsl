#version 450 core

out vec4 outColor;

in vec2 blurTextureCoordinates[11];

uniform sampler2D originalTexture;

void main() 
{
    outColor = vec4(0);
    outColor += texture(originalTexture, blurTextureCoordinates[0]) * 0.0093;
    outColor += texture(originalTexture, blurTextureCoordinates[1]) * 0.028002;
    outColor += texture(originalTexture, blurTextureCoordinates[2]) * 0.065984;
    outColor += texture(originalTexture, blurTextureCoordinates[3]) * 0.121703;
    outColor += texture(originalTexture, blurTextureCoordinates[4]) * 0.175713;
    outColor += texture(originalTexture, blurTextureCoordinates[5]) * 0.198596;
    outColor += texture(originalTexture, blurTextureCoordinates[6]) * 0.175713;
    outColor += texture(originalTexture, blurTextureCoordinates[7]) * 0.121703;
    outColor += texture(originalTexture, blurTextureCoordinates[8]) * 0.065984;
    outColor += texture(originalTexture, blurTextureCoordinates[9]) * 0.028002;
    outColor += texture(originalTexture, blurTextureCoordinates[10]) * 0.0093;
}
