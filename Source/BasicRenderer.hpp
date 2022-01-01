#pragma once

#include <glm/glm.hpp>
#include <memory>

#include "Renderer.hpp"
#include "Vertex.hpp"
#include "Camera2D.hpp"

namespace BARE2D {
	class BasicRenderer : public Renderer
	{
	public:
		BasicRenderer(std::string& fragShader, std::string& vertShader, unsigned int perspectiveWidth = 2, unsigned int perspectiveHeight = 2);
		virtual ~BasicRenderer();
		
		virtual void init() override;
		virtual void preRender() override;
		
		/**
		 * @brief Sets the camera to a given pointer. This means that the renderer takes ownership
		 * @param camera The pointer to the camera.
		 */
		virtual void setCamera(std::shared_ptr<Camera2D> camera);
		
		/**
		 * @return Returns the Camera pointer. To be used only to link multiple renderers' cameras.
		 */
		std::shared_ptr<Camera2D> getCamera();
		
		virtual void draw(glm::vec4 destRect, glm::vec4 uvRect, GLuint texture, float depth, Colour colour = Colour(255, 255, 255, 255), float angle = 0.0f, glm::vec2 COR = glm::vec2(0.5f));
	
	protected:
		virtual void createRenderBatches() override;
		
		std::string m_fragShader, m_vertShader;
		
		std::vector<Glyph*> m_glyphs;
		
		std::shared_ptr<Camera2D> m_camera;
	};

}
