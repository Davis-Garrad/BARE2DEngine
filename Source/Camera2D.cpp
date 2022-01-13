#include "Camera2D.hpp"

#include <glm/gtc/matrix_transform.hpp>

namespace BARE2D {

	Camera2D::Camera2D() :
		m_screenWidth(1),
		m_screenHeight(1),
		m_cameraMatrix(glm::mat4(0.0f)),
		m_orthographicMatrix(glm::mat4(0.0f)),
		m_matrixNeedsUpdate(true) {

	}

	Camera2D::~Camera2D() {

	}

	void Camera2D::init(float screenWidth, float screenHeight) {
		// Set the necessary bits
		m_screenWidth = screenWidth;
		m_screenHeight = screenHeight;

		// Reset the necessary bits
		m_state.scale = glm::vec2(1.0f);
		m_state.position = glm::vec2(0.0f);
		m_lastState = m_state;

		// Specifies a 2D coordinate system from 0.0-screenWidth in the X dimension and 0.0-screenHeight in the y direction.
		// Allows for transformation from an unbounded/3D system to a 2D projection.
		m_orthographicMatrix = glm::ortho(0.0f, (float)m_screenWidth, 0.0f, (float)m_screenHeight);
		m_cameraMatrix = glm::mat4(0.0f);

		// Make sure we update possible old stuff and initialize new stuff otherwise.
		m_matrixNeedsUpdate = true;
	}

	void Camera2D::update() {
		// Check if we need to do expensive operations
		if(m_matrixNeedsUpdate) {
			// Shit. We do need to.
			// First, find the world's translation relative to the camera.
			glm::vec3 translation = glm::vec3(m_screenWidth, m_screenHeight, 0.0f)/2.0f-glm::vec3(m_state.position.x, m_state.position.y, 0.0f);

			// Multiply by our transforming vector to actually move it.
			m_cameraMatrix = glm::translate(m_orthographicMatrix, translation);


			// Find the scale of the camera
			glm::vec3 scale = glm::vec3(m_state.scale.x, m_state.scale.y, 0.0f);

			// Multiply by our scale matrix.
			m_cameraMatrix = glm::scale(glm::mat4(1.0f), scale) * m_cameraMatrix;

			// Make sure we don't have to do this again every goddamn frame
			m_matrixNeedsUpdate = false;
		}
	}

	glm::vec4 Camera2D::getScreenSpaceFromViewSpace(glm::vec4 destRect) {
		glm::vec4 res(0.0f);
		glm::vec2 pos = getScreenPositionFromViewedPosition(glm::vec2(destRect.x, destRect.y));
		glm::vec2 size = getScreenSizeFromViewedSize(glm::vec2(destRect.w, destRect.z));
		res = glm::vec4(pos.x, pos.y, size.x, size.y);

		return res;
	}

	glm::vec4 Camera2D::getViewSpaceFromScreenSpace(glm::vec4 destRect) {
		glm::vec4 res(0.0f);
		glm::vec2 pos = getViewedPositionFromScreenPosition(glm::vec2(destRect.x, destRect.y));
		glm::vec2 size = getViewedSizeFromScreenSize(glm::vec2(destRect.w, destRect.z));
		res = glm::vec4(pos.x, pos.y, size.x, size.y);

		return res;
	}

	glm::vec2 Camera2D::getScreenPositionFromViewedPosition(glm::vec2 viewedPosition) {
		// Converts position from viewspace to screenspace.
		// Viewspace goes from (campos - size/(2scale)) -> (campos + size/(2scale))
		// Screenspace goes from (-1,-1)->(1,1)

		glm::vec2 maxAmplitude = (glm::vec2(m_screenWidth, m_screenHeight) / 2.0f) / m_state.scale;

		glm::vec2 screenPosition = viewedPosition - m_state.position;
		screenPosition /= maxAmplitude;

		return screenPosition;
	}

	glm::vec2 Camera2D::getViewedPositionFromScreenPosition(glm::vec2 screenPosition) {
		// Converts position from screenspace to viewspace.
		// Viewspace goes from (campos - size/(2scale)) -> (campos + size/(2scale))
		// Screenspace goes from (-1,-1)->(1,1)

		glm::vec2 maxAmplitude = (glm::vec2(m_screenWidth, m_screenHeight) / 2.0f) / m_state.scale;

		glm::vec2 viewedPosition = screenPosition * maxAmplitude;
		viewedPosition += m_state.position;

		return viewedPosition;
	}

	glm::vec2 Camera2D::getScreenSizeFromViewedSize(glm::vec2 viewedSize) {
		// Literally just treat viewedSize as a rectangle from (0, 0) (centre in both spaces) -> (viewedSize)
		glm::vec2 fullMagnitude = (glm::vec2(m_screenWidth, m_screenHeight) / 2.0f) / m_state.scale;

		glm::vec2 screenSize = viewedSize / fullMagnitude;

		return screenSize;
	}

	glm::vec2 Camera2D::getViewedSizeFromScreenSize(glm::vec2 screenSize) {
		// Literally just treat screenSize as a rectangle from (0, 0) (centre in both spaces) -> (screenSize)
		glm::vec2 fullMagnitude = (glm::vec2(m_screenWidth, m_screenHeight) / 2.0f) / m_state.scale;

		glm::vec2 viewedSize = screenSize * fullMagnitude;

		return viewedSize;
	}

	void Camera2D::setPosition(glm::vec2 newPos) {
		m_lastState = m_state;

		m_state.position = newPos;
		m_matrixNeedsUpdate = true;
	}

	void Camera2D::offsetPosition(glm::vec2 offset) {
		m_lastState = m_state;

		m_state.position += offset;
		m_matrixNeedsUpdate = true;
	}

	void Camera2D::setScale(float newScaleX, float newScaleY) {
		m_lastState = m_state;

		m_state.scale.x = newScaleX;
		m_state.scale.y = newScaleY;
		m_matrixNeedsUpdate = true;
	}

	void Camera2D::offsetScale(float offsetX, float offsetY) {
		// Set the state before modification to the current state, then modify
		m_lastState = m_state;

		m_state.scale.x += offsetX;
		m_state.scale.y += offsetY;
		m_matrixNeedsUpdate = true;
	}

	float Camera2D::getScreenWidth() const {
		return m_screenWidth;
	}

	float Camera2D::getScreenHeight() const {
		return m_screenHeight;
	}

	glm::vec2 Camera2D::getPosition() const {
		return m_state.position;
	}

	float Camera2D::getScaleX() const {
		return m_state.scale.x;
	}

	float Camera2D::getScaleY() const {
		return m_state.scale.y;
	}

	const glm::mat4& Camera2D::getCameraMatrix() const {
		return m_cameraMatrix;
	}

	bool Camera2D::isRectInScene(glm::vec4& rectangle) {

		glm::vec4 screenSpaceRect = getScreenSpaceFromViewSpace(rectangle);

		// Check if either of the positive x or negative x sides are too far to be seen
		if(screenSpaceRect.x + screenSpaceRect.z < -1.0f || screenSpaceRect.x > 1.0f) {
			return false;
		}

		// Check if the y value causes un-seeability
		if(screenSpaceRect.y + screenSpaceRect.w < -1.0f || screenSpaceRect.y > 1.0f) {
			return false;
		}

		return true;
	}

	CameraState Camera2D::getState() {
		return m_state;
	}

	CameraState Camera2D::getLastState() {
		return m_lastState;
	}


}
