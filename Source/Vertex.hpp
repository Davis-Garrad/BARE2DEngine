#pragma once

#include <GL/glew.h>
#include <glm/glm.hpp>

namespace BARE2D {

	/**
	 * @class Position
	 * @brief Positional data
	 */
	struct Position {
		float x, y, z;
	};
	
	/**
	 * @class Colour
	 * @brief An RGBA 8-bit colour value
	 */
	struct Colour {
		Colour() {}
		Colour(GLubyte R, GLubyte G, GLubyte B, GLubyte A) : r(R), g(G), b(B), a(A) {}
		
		GLubyte r, g, b, a;
	};
	
	/**
	 * @class UV
	 * @brief Holds two floats which can act as UV sizes or positions
	 */
	struct UV {
		float u, v;
	};
	
	/**
	 * @class Vertex
	 * @brief Just holds vertex data for convenience
	 */
	struct Vertex {
		Position position;
		
		Colour colour;
		
		UV uv;
		
		/**
		 * @brief Literally just sets the position. Convenient
		 * @param x
		 * @param y
		 * @param z
		 */
		void setPosition(float x, float y, float z) {
			position.x = x;
			position.y = y;
			position.z = z;
		}
		
		/**
		 * @brief Sets the colour.
		 * @param r
		 * @param g
		 * @param b
		 * @param a
		 */
		void setColour(GLubyte r, GLubyte g, GLubyte b, GLubyte a) {
			colour.r = r;
			colour.g = g;
			colour.b = b;
			colour.a = a;
		}
		
		/**
		 * @brief Sets the UV coords/dimensions.
		 * @param u
		 * @param v
		 */
		void setUV(float u, float v) {
			uv.u = u;
			uv.v = v;
		}
	};
	
	/**
	 * @class Glyph
	 * @brief The glyph represents a renderbatch's primitive data, which is created from each draw call in the basic renderer.
	 */
	class Glyph {
	public:
		Glyph(glm::vec4& destRect, glm::vec4& uvRect, GLuint Texture, float Depth, Colour colour);
		
		// Texture handle from opengl
		GLuint texture;
		
		// Depth for depth-culling.
		float depth;
		
		// Vertices prettty much just hold vertex data together. Useful in creating render batches
		Vertex topLeft, bottomLeft, topRight, bottomRight;
	};
}
