#version 130

in vec3 fragmentPosition;
in vec4 fragmentColour;
in vec2 fragmentUV;

out vec4 colour;

uniform sampler2D textureSampler;

void main() {
	colour = texture(textureSampler, fragmentUV.xy) * fragmentColour;
}

