#pragma once

#include <glm/glm.hpp>

namespace BARE2D {
	
	/**
	 * @class CameraState
	 * @brief Holds some basic information that the camera holds in a state.
	 */
	struct CameraState {
		glm::vec2 position = glm::vec2(0.0f);
		glm::vec2 scale = glm::vec2(1.0f);
	};

	/**
	 * @class Camera2D
	 * @brief The basic camera for a 2D world.
	 */
	class Camera2D
	{
	public:
		Camera2D();
		~Camera2D();
		
		/**
		 * @brief Initializes the camera
		 * @param screenWidth The width of the screen or FBO the camera needs to transform things within. The 'visual field'
		 * @param screenHeight The height of the screen or FBO the camera needs to transform things within. The 'visual field'
		 */
		void init(float screenWidth, float screenHeight);
		
		/**
		 * @brief Updates the matrix if necessary
		 */
		void update();
		
		/**
		 * @return Returns the on-screen position (from 0 to screenWidth, screenHeight)
		 */
		glm::vec2 getScreenPositionFromViewedPosition(glm::vec2 viewedPosition);
		
		/**
		 * @return Returns the in-camera position
		 */
		glm::vec2 getViewedPositionFromScreenPosition(glm::vec2 screenPosition);
		
		/**
		 * @return Returns the on-screen size. 
		 */
		glm::vec2 getScreenSizeFromViewedSize(glm::vec2 viewedSize);
		
		/**
		 * @return Returns the in-camera size 
		 */
		glm::vec2 getViewedSizeFromScreenSize(glm::vec2 screenSize);
		
		/**
		 * @brief Sets the position of the camera to newPos 
		 * @param newPos The position to set to
		 */
		void setPosition(glm::vec2 newPos);
		
		/**
		 * @brief Offsets the x and y position of the camera by some increment
		 * @param offset The x and y increments.
		 */
		void offsetPosition(glm::vec2 offset);
		
		/**
		 * @brief Sets the scale of the camera
		 * @param newScaleX The scale to set ot
		 * @param newScaleY The scale to set ot
		 */
		void setScale(float newScaleX, float newScaleY);
		
		/**
		 * @brief Offsets the scale by some increment 
		 * @param offsetX The increment of scale to add.
		 * @param offsetY The increment of scale to add.
		 */
		void offsetScale(float offsetX, float offsetY);
		
		/**
		 * @return The screen width 
		 */
		float getScreenWidth() const;
		/**
		 * @return The screen height 
		 */
		float getScreenHeight() const;
		/**
		 * @return The camera position 
		 */
		glm::vec2 getPosition() const;
		/**
		 * @return The zoom level 
		 */
		float getScaleX() const;
		float getScaleY() const;
		/**
		 * @return The camera matrix. 
		 */
		const glm::mat4& getCameraMatrix() const;
		
		/**
		 * @brief Checks if a rectangle is within the scene covered by the camera
		 * @param rectangle The rectangle to check against (format: x0, y0, w, h)
		 * @return True if the rectangle is see-able
		 */
		bool isRectInScene(glm::vec4& rectangle);
		
		/**
		 * @return The camera's current state. 
		 */
		CameraState getState();
		/**
		 * @return The camera's last state before modification of the current state. 
		 */
		CameraState getLastState();
		
	private:
		// The size of the screen (the camera's viewing field)
		float m_screenWidth, m_screenHeight;
		// This holds the state of the camera - the position as well as scale.
		CameraState m_state;
		// Holds the last state - only changes after being modified
		CameraState m_lastState;
		
		// Some matrices for math purposes.
		glm::mat4 m_cameraMatrix, m_orthographicMatrix;
		// If we change something simple, we need to update the complicated stuff.
		bool m_matrixNeedsUpdate = false;

	};

}

