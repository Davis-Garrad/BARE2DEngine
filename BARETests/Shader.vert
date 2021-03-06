#version 330
//The vertex shader operates on each vertex

//input data from the VBO. Each vertex is 3 floats
in vec3 vertexPosition;
in vec4 vertexColour;
in vec2 vertexUV;

out vec3 fragmentPosition;
out vec4 fragmentColour;
out vec2 fragmentUV;

uniform mat4 projectionMatrix = mat4(1.0);

void main() {
	gl_Position.xy = vec4(projectionMatrix * vec4(vertexPosition.xyz, 1.0)).xy;
	gl_Position.z = vertexPosition.z;
	gl_Position.w = 1.0;

	fragmentPosition = vertexPosition;
	fragmentUV = vec2(vertexUV.x, 1.0 - vertexUV.y);
	fragmentColour = vertexColour;
}

