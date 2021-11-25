#pragma once

#include "BasicRenderer.hpp"

namespace BARE2D {
	
	class Camera2D;

	class CameraRenderer : public BasicRenderer
	{
	public:
		CameraRenderer(std::string& fragShader, std::string& vertShader, unsigned int perspectiveWidth, unsigned int perspectiveHeight);
		~CameraRenderer();
		
		virtual void init() override;
		
		virtual void draw(glm::vec4 destRect, glm::vec4 uvRect, GLuint texture, float depth) override;
		
		Camera2D* getCamera() {
			return m_camera;
		}
		
	protected:
		virtual void preRender() override;
		
		/**
		 * @brief Checks if a rectangle is within the scene covered by the camera
		 * @param rectangle The rectangle to check against (format: x0, y0, w, h)
		 * @return True if the rectangle is see-able
		 */
		bool isRectInScene(glm::vec4& rectangle);
	
		Camera2D* m_camera = nullptr;

	};

}

