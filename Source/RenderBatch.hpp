#pragma once

#include <GL/glew.h>

/**
 * @class RenderBatch
 * @brief The RenderBatch essentially represents a single drawn object - normally 6 vertices (a rectangle), but can be otherwise.
 */
class RenderBatch
{
public:
	RenderBatch(GLuint Offset, GLuint NumVertices, GLuint TextureID) : offset(Offset), numVertices(NumVertices), textureID(TextureID) {
		
	}
	GLuint offset;
	GLuint numVertices;
	GLuint textureID;

};

