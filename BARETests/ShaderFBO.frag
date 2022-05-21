#version 330

in vec3 fragmentPosition;
in vec4 fragmentColour;
in vec2 fragmentUV;

out vec4 colour0;

uniform sampler2D colourTexture0; // Regular colours
uniform sampler2D colourTexture1; // Bump map!

uniform vec2 mousePos;

void main() {
	vec3 normal = (texture(colourTexture1, fragmentUV.xy)).rgb;
	vec4 texColour = texture(colourTexture0, fragmentUV.xy);

	colour0 = texColour * fragmentColour;
	
	normal.rg *= 2.0;
	normal.rg -= 1.0;
	normal.b *= -2.0;
	normal.b += 1.0;
	vec3 lightSource = vec3(mousePos, -0.05);//vec3(cos(time * 0.01), sin(time * 0.01), -1.0);
	
	float brightness = abs(dot(normal, normalize(lightSource - fragmentPosition)) / (5.0 * distance(fragmentPosition.xy, lightSource.xy) + 1.0));
	
	colour0.rgb *= min(brightness, 1.0);
}

