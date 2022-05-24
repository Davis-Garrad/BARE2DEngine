#version 330

in vec3 fragmentPosition;
in vec4 fragmentColour;
in vec2 fragmentUV;

out vec4 colour0;

uniform sampler2D colourTexture0; // Regular colours
uniform sampler2D colourTexture1; // Bump map!
uniform sampler2D colourTexture2; // Extra one for shits and giggles.
uniform sampler2D depthTexture; // depth

uniform vec2 mousePos;

void main() {
	vec3 normal = (texture(colourTexture1, fragmentUV.xy)).xyz;
	vec4 texColour = texture(colourTexture0, fragmentUV.xy) * 0.4 + texture(colourTexture2, fragmentUV.xy) * 0.6;

	colour0 = texColour * fragmentColour;
	
	normal.rg *= 2.0;
	normal.rg -= 1.0;
	normal.b *= -2.0;
	normal.b += 1.0;
	vec3 lightSource = vec3(mousePos, -0.05);//vec3(cos(time * 0.01), sin(time * 0.01), -1.0);
	
	float depth = texture(depthTexture, fragmentUV.xy).r / 2.0;
	float intensity = 80.0;
	float falloff = 4.0;
	vec3 pos = vec3(fragmentPosition.xy, depth);
	float distance = distance(pos.xyz, lightSource.xyz) * 10.0;
	
	float brightness = intensity * abs(dot(normal, normalize(lightSource - pos))) / pow(distance, falloff);
	
	colour0.rgb *= min(brightness, 1.0);
}

