#pragma once

#include <glm/glm.hpp>

namespace BARE2D {

	/**
	 * @class CameraState
	 * @brief Holds some basic information that the camera holds in a state.
	 */
	struct CameraState {
		glm::vec2 focus = glm::vec2(0.0f);
		glm::vec2 scale = glm::vec2(1.0f);
	};

	/**
	 * @class Camera2D
	 * @brief The basic camera for a 2D world. There are two spaces - the Worldspace and the Viewspace.
	 * The Worldspace is standard for all cameras, it is the 'gameworld' space.
	 * The Viewspace is the subspace of the worldspace. It is what the camera captures.
	 * Scale is zoom factor. NOT resolution scalar.
	 */
	class Camera2D {
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
			 * @brief Converts a coordinate from Worldspace to Viewspace
			 * @param pos A point in Viewspace
			 * @return The converted point in Worldspace.
			 */
			glm::vec2 getWorldspaceCoord(glm::vec2 pos) const;

			/**
			 * @brief Converts a coordinate from Worldspace to Viewspace
			 * @param pos A point in Worldspace
			 * @return The converted point in Viewspace.
			 */
			glm::vec2 getViewspaceCoord(glm::vec2 pos) const;

			/**
			 * @return The Worldspace size from a Viewspace size
			 */
			glm::vec2 getWorldspaceSize(glm::vec2 size) const;

			/**
			 * @return The Viewspace size from a Worldspace size
			 */
			glm::vec2 getViewspaceSize(glm::vec2 size) const;

			/**
			 * @return The Worldspace rectangle (dest/rect) from a Viewspace rectangle (dest/rect)
			 */
			glm::vec4 getWorldspaceRect(glm::vec4 destRect) const;

			/**
			 * @return The Viewspace rectangle (dest/rect) from a Worldspace rectangle (dest/rect)
			 */
			glm::vec4 getViewspaceRect(glm::vec4 destRect) const;

			/**
			 * @brief Sets the center of the camera to newFocus
			 * @param newFocus The position to set the center of the camera to
			 */
			void setFocus(glm::vec2 newFocus);

			/**
			 * @brief Moves the center of the camera to focus + deltaPos
			 * @param deltaPos The change to move by
			 */
			void offsetFocus(glm::vec2 deltaPos);

			/**
			 * @brief Sets the scale of the camera
			 * @param newScaleX The scale to set ot
			 * @param newScaleY The scale to set ot
			 */
			void setScale(float newScaleX, float newScaleY);

			/**
			 * @brief Adds to the zoom factor of the camera.
			 * @param deltaScaleX The x direction
			 * @param deltaScaleY The y direction
			 */
			void offsetScale(float deltaScaleX, float deltaScaleY);

			/**
			 * @return The POV size
			 */
			glm::vec2 getViewspaceResolution() const;

			/**
			 * @return The camera focus
			 */
			glm::vec2 getFocus() const;

			/**
			 * @return The camera's bottom-left position.
			 */
			glm::vec2 getStatePosition() const;

			/**
			 * @return The zoom levels
			 */
			glm::vec2 getScale() const;

			/**
			 * @return The camera matrix.
			 */
			const glm::mat4& getCameraMatrix() const;

			bool isRectInViewspace(glm::vec4& destRect) const;

			/**
			 * @return The camera's current state.
			 */
			CameraState getState();
			/**
			 * @return The camera's last state before modification of the current state.
			 */
			CameraState getLastState();

		private:
			// The size of the POV.
			glm::vec2 m_resolution;
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
