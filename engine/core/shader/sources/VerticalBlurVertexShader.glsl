#version 450 core

in vec2 position;

uniform float targetHeight;

out vec2 blurTextureCoordinates[11];

void main()
{
    gl_Position = vec4(position, 0.0, 1.0);
    vec2 centerTextureCoordinates = position * 0.5 + 0.5;

    float pixelSize = 1.0 / targetHeight;

    for (int i = -5; i <= 5; ++i)
    {
        blurTextureCoordinates[i + 5] = centerTextureCoordinates + vec2(0.0, pixelSize * i);
    }
}
