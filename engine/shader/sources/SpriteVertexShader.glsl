#version 450 core

in vec2 position;

out vec2 textureCoords;

uniform int row;
uniform int col;
uniform int currentRow;
uniform int currentCol;

uniform mat4 transformationMatrix;

void main()
{
    gl_Position = transformationMatrix * vec4(position, 0.0, 1.0);
    textureCoords = position / 2.0 + vec2(0.5);

    textureCoords.x = textureCoords.x / col + float(currentCol) / col;
    textureCoords.y = textureCoords.y / row + float(currentRow) / row;
}
