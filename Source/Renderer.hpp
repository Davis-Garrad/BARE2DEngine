#pragma once

#include <vector>

#include "ShaderProgram.hpp"
#include "VAO.hpp"
#include "RenderBatch.hpp"

namespace BARE2D {

	/**
	 * @class Renderer
	 * @brief The renderer class holds some shader program, manages some VBO, some render batch(es), and allows customizable, simple rendering.
	 */
	class Renderer
	{
	public:
		Renderer();
		virtual ~Renderer();
		
		/**
		 * @brief Clears the necessary vectors, etc. to prepare for draw() calls, etc.
		 */
		virtual void begin();
		
		/**
		 * @brief Creates the renderbatches, does necessary stuff before render() call.
		 */
		virtual void end();
		
		/**
		 * @brief Initializes all necessary bits of the renderer.
		 */
		virtual void init();
		
		/**
		 * @brief Initializes all uniforms, such as colour attachments, depth attachments, etc.
		 */
		virtual void initUniforms();
		
		/**
		 * @brief Frees all necessary memory.
		 */
		virtual void destroy();
		
		/**
		 * @brief Actually renders the contents to the screen!
		 */
		virtual void render();
		
		ShaderProgram* getShader();
		
	protected:
		/**
		 * @brief Does stuff inside of the render function, within the shader's use.
		 */
		virtual void preRender() {};
		
		/**
		 * @brief Constructs all of the render batches from data given by, say, draw() calls.
		 */
		virtual void createRenderBatches() = 0;
		
		ShaderProgram m_shader; // The shader to draw with.
		VAO m_vertexArrayObject; // Holds all of the vertex buffer object info - the actual uploaded information.
		std::vector<RenderBatch> m_batches; // Holds all glyphs (a renderbatch is equal to a drawn sprite, for example)
	};

}

