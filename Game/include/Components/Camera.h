#ifndef _CAMERA_H
#define _CAMERA_H

#include "Component.h"

class Camera:public Component
{
public:
  Camera();
  ~Camera();

  void onUpdate();

  void setLookAt(vec3& look)
  {
    m_LookAt=look;
  };

  void setUp(vec3& up)
  {
    m_Up=up;
  }

  void setAspectRatio(float aspectRatio)
  {
    m_AspectRatio=aspectRatio;
  };

  void setFOV(float fov)
  {
    m_FOV=fov;
  };

  void setNearClip(float nearClip)
  {
	  m_NearClip = nearClip;
  };

  void setFarClip(float farClip)
  {
	  m_FarClip = farClip;
  };

  mat4& getProjection()
  {
    return m_Projection;
  };

  mat4& getView()
  {
    return m_View;
  };
private:
  vec3 m_LookAt;
  vec3 m_Up;
  float m_AspectRatio;
  float m_FOV;
  float m_NearClip;
  float m_FarClip;
  mat4 m_View;
  mat4 m_Projection;
};

#endif
