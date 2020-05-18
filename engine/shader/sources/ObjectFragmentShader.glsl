#version 450 core

in vec2 textCoords;
in vec3 surfaceNormal;
in vec3 worldPosition;

uniform sampler2D objectTexture;
uniform vec3 lightPosition;
uniform vec3 lightColor;
uniform vec3 cameraPosition;

out vec4 outColor;

void main()
{
    vec3 lightPos = normalize(lightPosition);
    vec4 textureColor = texture(objectTexture, textCoords);

    const float ambientFactor = 0.2;
    vec3 ambient = lightColor * ambientFactor;

    vec3 lightDirection = normalize(lightPos - worldPosition);

    float diffuseFactor = max(dot(surfaceNormal, lightPos), 0.0);
    vec3 diffuse = lightColor * diffuseFactor;

    vec3 toCameraVector = normalize(cameraPosition - worldPosition);
    vec3 reflectedVector = reflect(-lightDirection, surfaceNormal);

    float specularFactor = max(dot(reflectedVector, toCameraVector), 0.0);
    specularFactor = pow(specularFactor, 2);
    const float material = 0.7;

    vec3 specular = specularFactor * material * lightColor;

    vec3 totalColor = (diffuse + ambient + specular) * textureColor.rgb;
    outColor = vec4(totalColor, 1.0);
}
