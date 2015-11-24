#ifndef _CAMERA_H
#define _CAMERA_H

#include "Common.h"



class Camera
{
public:

	Camera();
	~Camera();

	void onUpdate();

	void setCamPos(vec3& pos)
	{
		m_CameraPosition = pos;
	};

	void setFOV(float fov)
	{
		m_FOV = fov;
	};

	void setAspectRatio(float ratio)
	{
		m_AspectRatio = ratio;
	};

	void setNearClip(float nearClip)
	{
		m_NearClip = nearClip;
	};

	void setFarClip(float farClip)
	{
		m_FarClip = farClip;
	};

	mat4& getViewMatrix()
	{
		return m_ViewMatrix;
	};

	mat4& getProjMatrix()
	{
		return m_ProjMatrix;
	};

private:

	mat4 m_ViewMatrix;
	mat4 m_ProjMatrix;
	vec3 m_CameraPosition;
	float m_AspectRatio;
	float m_FOV;
	float m_NearClip;
	float m_FarClip;


protected:


};


#endif