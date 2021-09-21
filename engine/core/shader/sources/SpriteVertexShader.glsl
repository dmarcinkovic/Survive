#version 450 core

layout (location = 0) in vec2 position;

out vec2 textureCoords;

uniform int row;
uniform int col;
uniform int spriteIndex;

uniform mat4 transformationMatrix;
uniform mat4 projectionMatrix;

void main()
{
    int currentCol = spriteIndex % col;
    int currentRow = spriteIndex / col;
    currentRow = row - currentRow - 1;

    gl_Position = projectionMatrix * transformationMatrix * vec4(position, 0.0, 1.0);
    textureCoords = position / 2.0 + vec2(0.5);

    textureCoords.x = textureCoords.x / col + float(currentCol) / col;
    textureCoords.y = textureCoords.y / row + float(currentRow) / row;
}
