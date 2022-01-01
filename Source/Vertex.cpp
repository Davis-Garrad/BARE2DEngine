#include "Vertex.hpp"

namespace BARE2D {
	Glyph::Glyph(glm::vec4& destRect, glm::vec4& uvRect, GLuint& Texture, float& Depth, Colour& colour) : texture(Texture), depth(Depth) {
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
	
	Glyph::Glyph(glm::vec4& destRect, glm::vec4& uvRect, GLuint& Texture, float& Depth, Colour& colour, float& angle) : texture(Texture), depth(Depth) {
		glm::vec2 centrePoint = glm::vec2(destRect.z, destRect.w) * glm::vec2(0.5f);

		// Get points centered at origin
		glm::vec2 tl(-centrePoint.x, centrePoint.y);
		glm::vec2 bl(-centrePoint.x, -centrePoint.y);
		glm::vec2 br(centrePoint.x, -centrePoint.y);
		glm::vec2 tr(centrePoint.x, centrePoint.y);

		// Rotate the points
		tl = rotatePoint(tl, angle) + centrePoint;
		bl = rotatePoint(bl, angle) + centrePoint;
		br = rotatePoint(br, angle) + centrePoint;
		tr = rotatePoint(tr, angle) + centrePoint;
		
		topLeft.colour = colour;
		topLeft.setPosition(destRect.x + tl.x, destRect.y + tl.y, depth);
		topLeft.setUV(uvRect.x, uvRect.y + uvRect.w);

		bottomLeft.colour = colour;
		bottomLeft.setPosition(destRect.x + bl.x, destRect.y + bl.y, depth);
		bottomLeft.setUV(uvRect.x, uvRect.y);

		bottomRight.colour = colour;
		bottomRight.setPosition(destRect.x + br.x, destRect.y + br.y, depth);
		bottomRight.setUV(uvRect.x + uvRect.z, uvRect.y);

		topRight.colour = colour;
		topRight.setPosition(destRect.x + tr.x, destRect.y + tr.y, depth);
		topRight.setUV(uvRect.x + uvRect.z, uvRect.y + uvRect.w);
	}
	
	Glyph::Glyph(glm::vec4& destRect, glm::vec4& uvRect, GLuint& Texture, float& Depth, Colour& colour, float& angle, glm::vec2& COR) : texture(Texture), depth(Depth) {
		glm::vec2 centrePoint = glm::vec2(destRect.z, destRect.w) * COR;
		glm::vec2 invCentrePoint = glm::vec2(destRect.z, destRect.w) * (1.0f - COR);

		// Get points centered at origin
		glm::vec2 tl(-invCentrePoint.x, centrePoint.y);
		glm::vec2 bl(-invCentrePoint.x, -invCentrePoint.y);
		glm::vec2 br(centrePoint.x, -invCentrePoint.y);
		glm::vec2 tr(centrePoint.x, centrePoint.y);

		// Rotate the points
		tl = rotatePoint(tl, angle) + centrePoint;
		bl = rotatePoint(bl, angle) + centrePoint;
		br = rotatePoint(br, angle) + centrePoint;
		tr = rotatePoint(tr, angle) + centrePoint;
		
		topLeft.colour = colour;
		topLeft.setPosition(destRect.x + tl.x, destRect.y + tl.y, depth);
		topLeft.setUV(uvRect.x, uvRect.y + uvRect.w);

		bottomLeft.colour = colour;
		bottomLeft.setPosition(destRect.x + bl.x, destRect.y + bl.y, depth);
		bottomLeft.setUV(uvRect.x, uvRect.y);

		bottomRight.colour = colour;
		bottomRight.setPosition(destRect.x + br.x, destRect.y + br.y, depth);
		bottomRight.setUV(uvRect.x + uvRect.z, uvRect.y);

		topRight.colour = colour;
		topRight.setPosition(destRect.x + tr.x, destRect.y + tr.y, depth);
		topRight.setUV(uvRect.x + uvRect.z, uvRect.y + uvRect.w);
	}
	
	glm::vec2 Glyph::rotatePoint(const glm::vec2& pos, float& angle) {
		glm::vec2 newv;
		newv.x = pos.x * cos(angle) - pos.y * sin(angle);
		newv.y = pos.y * cos(angle) + pos.x * sin(angle);
		return newv;
	}
	
	
}
