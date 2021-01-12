#version 450 core

out vec4 outColor;

uniform vec4 pickingColor;

void main() {
    outColor = pickingColor;
}
