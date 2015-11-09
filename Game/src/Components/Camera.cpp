#include "Components/Camera.h"
#include "Components/Transform.h"
#include "GameObject.h"

Camera::Camera()
{
  m_Type="Camera";
  m_LookAt=vec3(0.0f,0.0f,0.0f);
  m_Up=vec3(0.0f,1.0f,0.0f);
  m_AspectRatio=1.3333f;
  m_FOV=45.0f;
  m_NearClip=1.0f;
  m_FarClip=100.0f;
  m_View=mat4(1.0f);
  m_Projection=mat4(1.0f);
}

Camera::~Camera()
{

}


void Camera::onUpdate()
{
  shared_ptr<Transform> t=static_pointer_cast<Transform>(m_pOwner->getComponent("Transform"));

  m_View=lookAt(t->getPosition(),m_LookAt,m_Up);
  m_Projection=perspective(m_FOV,m_AspectRatio,m_NearClip,m_FarClip);
}
