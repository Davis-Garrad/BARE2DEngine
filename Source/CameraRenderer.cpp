#include "CameraRenderer.hpp"

#include "Camera2D.hpp"

namespace BARE2D {

	CameraRenderer::CameraRenderer(std::string& fragShader, 
								   std::string& vertShader, 
								   unsigned int perspectiveWidth, 
								   unsigned int perspectiveHeight)
		: BasicRenderer(fragShader, vertShader) 
	{
		m_camera = new Camera2D();
		m_camera->init(perspectiveWidth, perspectiveHeight);
	}
	
	CameraRenderer::~CameraRenderer() {
		delete m_camera;
	}
	
	void CameraRenderer::init() {
		BasicRenderer::init();
	}
	
	void CameraRenderer::draw(glm::vec4 destRect, glm::vec4 uvRect, GLuint texture, float depth) {
		// Make sure it's actually in the scene.
		if(!isRectInScene(destRect))
			return;
		
		// At this point we can just scale the size (the position should be translated in the shader) and draw it
		glm::vec2 size = m_camera->getScreenSizeFromViewedSize(glm::vec2(destRect.z, destRect.w));
		
		// Just add the glyphs, etc.. We must do this explicitly, as calling the parent function seems to call it on an instance of the parent, not the self.
		m_glyphs.emplace_back(destRect, uvRect, texture, depth, Colour(255, 255, 255, 255));
	}
		
	
	void CameraRenderer::preRender() {
		BasicRenderer::preRender();
		
		m_camera->update();
		
		glm::mat4 projectionMatrix = m_camera->getCameraMatrix();
		
		m_shader.setUniformMatrix("P", GL_FALSE, projectionMatrix);
	}
	
	bool CameraRenderer::isRectInScene(glm::vec4& rectangle) {
		// Create the scene's rectangle.
		glm::vec2 pos0 = m_camera->getPosition();
		glm::vec2 pos1 = glm::vec2(m_camera->getScreenWidth(), m_camera->getScreenHeight()) / m_camera->getScale();
		
		// Check if either of the positive x or negative x sides are too far to be seen
		if(rectangle.x + rectangle.z + m_camera->getScreenWidth()/2 < pos0.x || rectangle.x > pos1.x) {
			return false;
		}
		
		// Check if the y value causes un-seeability
		if(rectangle.y + rectangle.w + m_camera->getScreenHeight()/2 < pos0.y || rectangle.y > pos1.y) {
			return false;
		}
		
		return true;
	}


}

