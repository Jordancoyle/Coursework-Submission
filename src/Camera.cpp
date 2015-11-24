#include <Camera.h>
#include <GameObject.h>
#include <Common.h>

Camera::Camera()
{
	m_ViewMatrix = mat4(1.0f);
	m_ProjMatrix = mat4(1.0f);
	m_CameraPosition = vec3(0.0f, 0.0f, 10.0f);
	m_AspectRatio = 640.0f / 480.0f;
	m_FOV = 45.0f;
	m_NearClip = 0.1f;
	m_FarClip = 100.0f;
}

Camera::~Camera()
{

}

void Camera::onUpdate()
{
	m_ProjMatrix = perspective(m_FOV, m_AspectRatio, m_NearClip, m_FarClip);

	m_ViewMatrix = lookAt(m_CameraPosition, vec3(0.0f, 0.0f, 0.0f), vec3(0.0f, 1.0f, 0.0f));
}