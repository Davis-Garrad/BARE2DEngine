#include "Vertex.hpp"

namespace BARE2D {
	Glyph::Glyph(glm::vec4& destRect, glm::vec4& uvRect, GLuint Texture, float Depth, Colour colour) : texture(Texture), depth(Depth) {
		topLeft.colour = colour;
		topLeft.setPosition(destRect.x, destRect.y + destRect.w, depth);
		topLeft.setUV(uvRect.x, uvRect.y + uvRect.w);

		bottomLeft.colour = colour;
		bottomLeft.setPosition(destRect.x, destRect.y, depth);
		bottomLeft.setUV(uvRect.x, uvRect.y);

		bottomRight.colour = colour;
		bottomRight.setPosition(destRect.x + destRect.z, destRect.y, depth);
		bottomRight.setUV(uvRect.x + uvRect.z, uvRect.y);

		topRight.colour = colour;
		topRight.setPosition(destRect.x + destRect.z, destRect.y + destRect.w, depth);
		topRight.setUV(uvRect.x + uvRect.z, uvRect.y + uvRect.w);
	}
}
