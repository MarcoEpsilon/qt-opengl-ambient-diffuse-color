#version 330
out vec4 fragColor;
uniform sampler2D tex;
in vec2 outTexCoord;
in vec4 outColor;
void main() {
    fragColor = texture(tex,outTexCoord) * outColor;
}