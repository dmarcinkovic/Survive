#version 450 core

layout (location = 0) in vec2 position;
layout (location = 1) in mat4 modelViewMatrix;
layout (location = 5) in float spriteIndex;

out vec2 textureCoordinates;

uniform mat4 projectionMatrix;
uniform uint numberOfRows;
uniform uint numberOfCols;

void main()
{
    uint index = uint(round(spriteIndex));

    uint currentCol = index % numberOfCols;
    uint currentRow = index / numberOfCols;
    currentRow = numberOfRows - currentRow - 1;

    textureCoordinates = position / 2.0 + vec2(0.5);
    textureCoordinates.x = textureCoordinates.x / numberOfCols + float(currentCol) / numberOfCols;
    textureCoordinates.y = textureCoordinates.y / numberOfRows + float(currentRow) / numberOfRows;

    gl_Position = projectionMatrix * modelViewMatrix * vec4(position, 0.0, 1.0f);
}
