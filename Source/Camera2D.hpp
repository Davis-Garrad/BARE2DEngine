#pragma once

#include <glm/glm.hpp>

namespace BARE2D {

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
		 * @param newScale The scale to set ot
		 */
		void setScale(float newScale);
		
		/**
		 * @brief Offsets the scale by some increment 
		 * @param offset The increment of scale to add.
		 */
		void offsetScale(float offset);
		
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
		float getScale() const;
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
		
	private:
		// The position of the camera
		glm::vec2 m_position = glm::vec2(0.0f);
		// The size of the screen (the camera's viewing field)
		float m_screenWidth, m_screenHeight;
		// How much the camera is zoomed in
		float m_scale = 1.0f;
		
		// Some matrices for math purposes.
		glm::mat4 m_cameraMatrix, m_orthographicMatrix;
		// If we change something simple, we need to update the complicated stuff.
		bool m_matrixNeedsUpdate = false;

	};

}

