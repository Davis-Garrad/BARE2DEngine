#version 130

in vec3 fragmentPosition;
in vec4 fragmentColour;
in vec2 fragmentUV;

out vec4 colour;

uniform sampler2D colourTexture;
uniform sampler2D depthTexture;

void main() {
	float depth = (texture(depthTexture, fragmentUV.xy)).r;

	colour.rgba = texture(colourTexture, fragmentUV.xy) * fragmentColour;
	colour.r *= depth;
}

