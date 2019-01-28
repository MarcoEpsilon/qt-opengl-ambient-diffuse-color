#version 330
layout (location = 0) in vec3 Position;
layout (location = 1) in vec2 texCoord;
layout (location = 2) in vec3 vertNormal;
struct Light {
    vec3 ambientLightQuality;
    float ambientLightIntensity;
    vec3 diffuseLightQuality;
    float diffuseLightIntensity;
    vec3 diffuseLightDirection;
};
uniform mat4 worldMatrix;
uniform Light fLight;
uniform mat4 modelMatrix;
out vec2 outTexCoord;
out vec4 outColor;
void main() {
    vec3 ambientFactor = fLight.ambientLightQuality * fLight.ambientLightIntensity;
    vec4 modelNormal = modelMatrix * vec4(vertNormal,1.0f);
    vec3 diffuseFactor = fLight.diffuseLightIntensity * fLight.diffuseLightQuality * max(0,dot(normalize(fLight.diffuseLightDirection),modelNormal.xyz));
    gl_Position = worldMatrix * vec4(Position,1.0f);
    outColor = vec4(ambientFactor + diffuseFactor,1.0f);
    outTexCoord = texCoord;
}