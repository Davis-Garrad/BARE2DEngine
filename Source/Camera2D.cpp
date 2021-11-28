#include "Camera2D.hpp"

#include <glm/gtc/matrix_transform.hpp>

namespace BARE2D {

	Camera2D::Camera2D() : 
							m_position(glm::vec2(0.0f)), 
							m_screenWidth(400), 
							m_screenHeight(400), 
							m_scale(1.0f), 
							m_cameraMatrix(glm::mat4(0.0f)), 
							m_orthographicMatrix(glm::mat4(0.0f)), 
							m_matrixNeedsUpdate(true)
	{
		
	}

	Camera2D::~Camera2D()
	{
		
	}

	void Camera2D::init(float screenWidth, float screenHeight)
	{
		// Set the necessary bits
		m_screenWidth = screenWidth;
		m_screenHeight = screenHeight;
		
		// Reset the necessary bits
		m_scale = 1.0f;
		m_position.x = 0.0f;
		m_position.y = 0.0f;
		
		// Specifies a 2D coordinate system from 0.0-screenWidth in the X dimension and 0.0-screenHeight in the y direction.
		// Allows for transformation from an unbounded/3D system to a 2D projection.
		m_orthographicMatrix = glm::ortho(0.0f, (float)m_screenWidth, 0.0f, (float)m_screenHeight);
		m_cameraMatrix = glm::mat4(0.0f);
		
		// Make sure we update possible old stuff and initialize new stuff otherwise.
		m_matrixNeedsUpdate = true;
	}

	void Camera2D::update()
	{
		// Check if we need to do expensive operations
		if(m_matrixNeedsUpdate) {
			// Shit. We do need to.
			// First, find the world's translation relative to the camera.
			glm::vec3 translation = glm::vec3(m_screenWidth / 2.0f - m_position.x, m_screenHeight / 2.0f - m_position.y, 0.0f);
			
			// Multiply by our transforming vector to actually move it.
			m_cameraMatrix = glm::translate(m_orthographicMatrix, translation);
			
			
			// Find the scale of the camera
			glm::vec3 scale = glm::vec3(m_scale, m_scale, 0.0f);
			
			// Multiply by our scale matrix.
			m_cameraMatrix = glm::scale(glm::mat4(1.0f), scale) * m_cameraMatrix;
			
			// Make sure we don't have to do this again every goddamn frame
			m_matrixNeedsUpdate = false;
		}
	}

	glm::vec2 Camera2D::getScreenPositionFromViewedPosition(glm::vec2 viewedPosition)
	{
		// Converts the viewed (in-camera) position to a screen-space position. The inverse of getViewedFromScreen.
		
		// Move them from the camera position
		viewedPosition -= m_position;
		
		// Scale them to the screen-space world
		// Make sure they aren't just getting destroyed if scale == 0.0f
		if(m_scale > 0.0f) {
			viewedPosition *= m_scale;
		}
		
		// Give the camera position back its offset to make it screen-space again
		//viewedPosition -= glm::vec2(m_screenWidth/2, m_screenHeight/2);
		
		// Lastly, (un?)invert the Y direction again.
		//viewedPosition.y = m_screenHeight - viewedPosition.y;
	
		// Now we have our result!
		return viewedPosition;
	}

	glm::vec2 Camera2D::getViewedPositionFromScreenPosition(glm::vec2 screenPosition)
	{
		// Converts the on-screen position to an in-camera position
		// First, invert the Y direction
		screenPosition.y = m_screenHeight - screenPosition.y;
		
		// Centre the screen coordinates
		//screenPosition += glm::vec2(m_screenWidth/2, m_screenHeight/2);
	
		// Scale them to the camera world
		// Make sure we aren't inverting them with a teeny scale somehow or dividing by zero
		if(m_scale > 0.0f) {
			screenPosition /= m_scale;
		}
		
		// Now move em along to the camera position
		screenPosition += m_position;
		
		// Now we have our result!
		return screenPosition;
	}

	glm::vec2 Camera2D::getScreenSizeFromViewedSize(glm::vec2 viewedSize)
	{
		// Converts an in-camera size to a screen-space size.
		// Offsets and stuff are unnecessary.
		// Just scale:
		viewedSize *= m_scale;
		
		// And since sizes are relative to their container, divide by the "scale" of the screen - the screenWidth and Height
		viewedSize /= glm::vec2(m_screenWidth/2, m_screenHeight/2);
		
		return viewedSize;
	}

	glm::vec2 Camera2D::getViewedSizeFromScreenSize(glm::vec2 screenSize)
	{
		// Does the opposite of getScreenSizefromViewed...
		// Multiplies by the "scale" of the screen to get it to the true size
		screenSize *= glm::vec2(m_screenWidth/2, m_screenHeight/2);
		
		// Divides by the camera's scale to put it back into the camera world
		screenSize /= m_scale;
		
		return screenSize;
	}

	void Camera2D::setPosition(glm::vec2 newPos)
	{
		m_position = newPos;
		m_matrixNeedsUpdate = true;
	}

	void Camera2D::offsetPosition(glm::vec2 offset)
	{
		m_position += offset;
		m_matrixNeedsUpdate = true;
	}

	void Camera2D::setScale(float newScale)
	{
		m_scale = newScale;
		m_matrixNeedsUpdate = true;
	}

	void Camera2D::offsetScale(float offset)
	{
		m_scale += offset;
		m_matrixNeedsUpdate = true;
	}

	float Camera2D::getScreenWidth() const
	{
		return m_screenWidth;
	}

	float Camera2D::getScreenHeight() const
	{
		return m_screenHeight;
	}

	glm::vec2 Camera2D::getPosition() const
	{
		return m_position;
	}

	float Camera2D::getScale() const
	{
		return m_scale;
	}

	const glm::mat4& Camera2D::getCameraMatrix() const
	{
		return m_cameraMatrix;
	}
	
	bool Camera2D::isRectInScene(glm::vec4& rectangle) {
		// Create the scene's rectangle.
		glm::vec2 pos0 = m_position - (glm::vec2(m_screenWidth / 2, m_screenHeight / 2) / m_scale);
		glm::vec2 pos1 = m_position + (glm::vec2(m_screenWidth / 2, m_screenHeight / 2) / m_scale);
		
		// Check if either of the positive x or negative x sides are too far to be seen
		if(rectangle.x + rectangle.z + m_screenWidth/2 < pos0.x || rectangle.x > pos1.x) {
			return false;
		}
		
		// Check if the y value causes un-seeability
		if(rectangle.y + rectangle.w + m_screenHeight/2 < pos0.y || rectangle.y > pos1.y) {
			return false;
		}
		
		return true;
	}


}
