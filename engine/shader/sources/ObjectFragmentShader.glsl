#version 450 core

in vec2 textCoords;
in vec3 surfaceNormal;
in vec3 worldPosition;

uniform sampler2D objectTexture;
uniform vec3 lightPosition;
uniform vec3 lightColor;

out vec4 outColor;

void main()
{
    vec4 textureColor = texture(objectTexture, textCoords);

    const float ambientFactor = 0.2;
    vec3 ambient = lightColor * ambientFactor;

    vec3 lightDirection = normalize(lightPosition - worldPosition);

    float diffuseFactor = max(dot(surfaceNormal, lightDirection), 0.0);
    vec3 diffuse = lightColor * diffuseFactor;

    vec3 totalColor = (diffuse + ambient) * textureColor.rgb;

    outColor = vec4(totalColor, 1.0);
}
