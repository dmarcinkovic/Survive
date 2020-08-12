#version 450 core

in vec3 surfaceNormal;
in vec2 texCoordinates;
in vec3 worldPosition;

uniform sampler2D objectTexture;
uniform vec3 lightPosition;
uniform vec3 lightColor;

out vec4 outColor;

void main()
{
    vec3 lightPos = normalize(lightPosition);
    vec4 textureColor = texture(objectTexture, texCoordinates);

    const float ambientFactor = 0.2;
    vec3 ambient = lightColor * ambientFactor;

    vec3 lightDirection = normalize(lightPos - worldPosition);
    const float diffuseFactor = max(dot(lightDirection, surfaceNormal), 0.0);
    vec3 diffuse = lightColor * diffuseFactor;

    vec3 totalColor = (diffuse + ambient) * textureColor.rgb;

    outColor = vec4(totalColor, 1.0);
}
