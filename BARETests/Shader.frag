#version 130

in vec3 fragmentPosition;
in vec4 fragmentColour;
in vec2 fragmentUV;

uniform sampler2D textureSampler;
uniform sampler2D bumpmapSampler;

out vec4 colour0;
out vec4 colour1;
out vec4 colour2;

void main() {
	colour0 = texture(textureSampler, fragmentUV.xy) * fragmentColour;
	colour1 = texture(bumpmapSampler, fragmentUV.xy);
	colour2 = vec4(sin(fragmentUV.x), sin(fragmentUV.y), cos(fragmentUV.x * fragmentUV.y), 1.0);
}

