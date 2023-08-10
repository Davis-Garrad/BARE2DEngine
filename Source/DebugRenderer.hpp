#pragma once

#include "Renderer.hpp"

#include <glm/glm.hpp>
#include <vector>

#include "Vertex.hpp"

namespace BARE2D {

	struct Line {
		void construct(glm::vec2 p0, glm::vec2 p1, float& thick, Colour& col);

		glm::vec2 point0;
		glm::vec2 point1;
		float thickness;
		Colour colour;
	};

	struct Circle {
		void construct(glm::vec2& p0, float& lineThick, float& radius, Colour& fillCol);

		glm::vec2 origin;
		std::vector<Line> lines;
	};

	struct Rectangle {
		void construct(glm::vec4& posSize, float& lineThick, Colour& fillCol);

		glm::vec4 destRect;
		Line lines[2];
	};

	/**
	 * @class DebugRenderer
	 * @author Davis-Dev
	 * @date 10/08/23
	 * @file DebugRenderer.hpp
	 * @brief A renderer specifically made for debugging purposes. Contains its own shaders.
	 */
	class DebugRenderer : public Renderer {
		public:
			DebugRenderer();
			virtual ~DebugRenderer();

			/**
			 * @brief Initializes with very rudimentary shaders (hardcoded), adds vertex attributes
			 */
			virtual void init() override;

			virtual void begin() override;

			virtual void render() override;

			/**
			 * @brief Draws a line
			 * @param point0 The origin
			 * @param point1 Where the line goes to
			 * @param thickness The thickness of the line
			 * @param colour The colour of the line
			 */
			virtual void drawLine(glm::vec2 point0, glm::vec2 point1, float thickness, Colour colour);

			/**
			 * @brief Draws a circle
			 * @param centre The centre point of the circle
			 * @param lineThickness The thickness of the lines creating the circle
			 * @param radius The radius of the circle
			 * @param lineColour The colour of the lines
			 * @param fillColour The fill of the circle
			 */
			virtual void drawCircle(glm::vec2 centre, float lineThickness, float radius, Colour fillColour = Colour(255, 255, 255, 255));

			/**
			 * @brief Draws a rectangle
			 * @param destRect The destination rectangle of the rectangle (position, then size)
			 * @param lineColour The colour of the lines that make up the rectangle
			 * @param fillColour The colour of the fill.
			 */
			virtual void drawRectangle(glm::vec4 destRect, float lineThickness, Colour fillColour = Colour(255, 255, 255, 255));

		protected:
			virtual void createRenderBatches() override;

			std::vector<Line> m_lines;
			std::vector<Circle> m_circles;
			std::vector<Rectangle> m_rectangles;

	};

}
