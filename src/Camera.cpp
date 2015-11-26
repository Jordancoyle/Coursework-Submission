#include <Camera.h>
#include <GameObject.h>
#include <Common.h>

Camera::Camera()
{
	m_ViewMatrix = mat4(1.0f);
	m_ProjMatrix = mat4(1.0f);
	m_CameraPosition = vec3(0.0f, 0.0f, 1.0f);
	m_CameraFront = vec3(0.0f, 0.0f, -1.0f);
	m_CameraLook = vec3(0.0f, 0.0f, 0.0f);
	m_CameraSpeed = 0.08f;
	m_AspectRatio = 640.0f / 480.0f;
	m_FOV = 45.0f;
	m_NearClip = 0.1f;
	m_FarClip = 100.0f;
}

Camera::~Camera()
{

}

void Camera::moveForward()
{
	m_CameraPosition += m_CameraSpeed * m_CameraFront;
}

void Camera::moveBackward()
{
	m_CameraPosition -= m_CameraSpeed * m_CameraFront;
}

void Camera::moveRight()
{
	m_CameraPosition += normalize(cross(m_CameraFront, vec3(0.0f, 0.1f, 0.0f))) * m_CameraSpeed;
}

void Camera::moveLeft()
{
	m_CameraPosition -= normalize(cross(m_CameraFront, vec3(0.0f, 0.1f, 0.0f))) * m_CameraSpeed;
}

void Camera::onUpdate()
{
	m_CameraLook = m_CameraPosition + m_CameraFront;

	m_ProjMatrix = perspective(m_FOV, m_AspectRatio, m_NearClip, m_FarClip);
	m_ViewMatrix = lookAt(m_CameraPosition, m_CameraLook, vec3(0.0f, 1.0f, 0.0f));
}