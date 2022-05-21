#include "Camera2D.hpp"

#include <glm/gtc/matrix_transform.hpp>

#include "Logger.hpp"

namespace BARE2D
{

Camera2D::Camera2D()
    : m_resolution(1.0f, 1.0f)
    , m_cameraMatrix(glm::mat4(0.0f))
    , m_orthographicMatrix(glm::mat4(0.0f))
    , m_matrixNeedsUpdate(true)
{
}

Camera2D::~Camera2D()
{
}

void Camera2D::init(float screenWidth, float screenHeight)
{
    // Set the necessary bits
    m_resolution = glm::vec2(screenWidth, screenHeight);

    // Reset the necessary bits
    m_state.scale = glm::vec2(1.0f);
    m_state.focus = m_resolution / 2.0f;
    m_lastState = m_state;

    // Specifies a 2D coordinate system from 0.0-screenWidth in the X dimension and 0.0-screenHeight in the y direction.
    // Allows for transformation from an unbounded/3D system to a 2D projection.
    m_orthographicMatrix = glm::ortho(0.0f, m_resolution.x, 0.0f, m_resolution.y);
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
	glm::vec2 statePosition = getStatePosition();
	glm::vec3 translation = -glm::vec3(statePosition.x, statePosition.y, 0.0f);

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

glm::vec2 Camera2D::getWorldspaceCoord(glm::vec2 pos) const
{
    // Inverse of viewspacecoord
    glm::vec2 result = pos;
    result -= m_state.focus;
    result *= m_state.scale;
    result += getStatePosition() - m_state.focus;

    return result;
}

glm::vec2 Camera2D::getViewspaceCoord(glm::vec2 pos) const
{
    glm::vec2 diffUnscaled = (pos - m_state.focus);
    glm::vec2 result = m_state.focus;

    result += getStatePosition() / m_state.scale;
    result += diffUnscaled / m_state.scale;

    return result;
}

glm::vec2 Camera2D::getWorldspaceSize(glm::vec2 size) const
{
    glm::vec2 result = size;

    size /= m_state.scale;

    return result;
}

glm::vec2 Camera2D::getViewspaceSize(glm::vec2 size) const
{
    glm::vec2 result = size;

    size *= m_state.scale;

    return result;
}

glm::vec4 Camera2D::getWorldspaceRect(glm::vec4 destRect) const
{
    glm::vec2 pos = glm::vec2(destRect.x, destRect.y);
    glm::vec2 size = glm::vec2(destRect.z, destRect.w);

    pos = getWorldspaceCoord(pos);
    size = getWorldspaceSize(size);

    return glm::vec4(pos.x, pos.y, size.x, size.y);
}

glm::vec4 Camera2D::getViewspaceRect(glm::vec4 destRect) const
{
    glm::vec2 pos = glm::vec2(destRect.x, destRect.y);
    glm::vec2 size = glm::vec2(destRect.z, destRect.w);

    pos = getViewspaceCoord(pos);
    size = getViewspaceSize(size);

    return glm::vec4(pos.x, pos.y, size.x, size.y);
}

void Camera2D::setFocus(glm::vec2 newFocus)
{
    m_lastState = m_state;

    m_state.focus = newFocus;

    m_matrixNeedsUpdate = true;
}

void Camera2D::offsetFocus(glm::vec2 deltaFocus)
{
    m_lastState = m_state;

    m_state.focus += deltaFocus;

    m_matrixNeedsUpdate = true;
}

void Camera2D::setScale(float newScaleX, float newScaleY)
{
    m_lastState = m_state;

    m_state.scale.x = newScaleX;
    m_state.scale.y = newScaleY;

    m_matrixNeedsUpdate = true;
}

void Camera2D::offsetScale(float deltaScaleX, float deltaScaleY)
{
    m_lastState = m_state;

    m_state.scale.x += deltaScaleX;
    m_state.scale.y += deltaScaleY;

    m_matrixNeedsUpdate = true;
}

glm::vec2 Camera2D::getViewspaceResolution() const
{
    return m_resolution;
}

glm::vec2 Camera2D::getFocus() const
{
    return m_state.focus;
}

glm::vec2 Camera2D::getScale() const
{
    return m_state.scale;
}

const glm::mat4& Camera2D::getCameraMatrix() const
{
    return m_cameraMatrix;
}

bool Camera2D::isRectInViewspace(glm::vec4& destRect) const
{
    return true;
}

CameraState Camera2D::getState()
{
    return m_state;
}

CameraState Camera2D::getLastState()
{
    return m_lastState;
}

glm::vec2 Camera2D::getStatePosition() const
{
    return m_state.focus - m_resolution / 2.0f;
}

}
