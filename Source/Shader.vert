#version 130
//The vertex shader operates on each vertex

//input data from the VBO. Each vertex is 3 floats
in vec3 vertexPosition;
in vec4 vertexColour;
in vec2 vertexUV;

out vec3 fragmentPosition;
out vec4 fragmentColour;
out vec2 fragmentUV;

void main() {
	gl_Position = vec4(vertexPosition.xyz/2000.0, 1.0);

	fragmentPosition = vertexPosition/2000.0;
	fragmentUV = vec2(vertexUV.x, 1.0 - vertexUV.y);
	fragmentColour = vertexColour;
}

