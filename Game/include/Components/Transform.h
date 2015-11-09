#ifndef _TRANSFORM_H
#define _TRANSFORM_H

#include "Common.h"
#include "Component.h"

class Transform:public Component
{
public:
  Transform()
  {
    m_Type="Transform";
    m_Position=vec3(0.0f,0.0f,0.0f);
    m_Rotation=vec3(0.0f,0.0f,0.0f);
    m_Scale=vec3(1.0f,1.0f,1.0f);

    m_ModelMatrix=mat4(1.0f);
    m_TranlationMatrix=mat4(1.0f);
    m_RotationalMatrix=mat4(1.0f);
    m_ScaleMatrix=mat4(1.0f);
  };
  ~Transform()
  {

  };

  void onUpdate();

  void setPosition(const vec3& pos)
  {
    m_Position=pos;
  };

  vec3& getPosition()
  {
    return m_Position;
  };

  void setRotatation(const vec3& rotation)
  {
    m_Rotation=rotation;
  };

  void setScale(const vec3& scale)
  {
    m_Scale=scale;
  };

  mat4& getModelMatrix()
  {
    return m_ModelMatrix;
  };

private:
  vec3 m_Position;
  vec3 m_Rotation;
  vec3 m_Scale;

  mat4 m_ModelMatrix;
  mat4 m_TranlationMatrix;
  mat4 m_RotationalMatrix;
  mat4 m_ScaleMatrix;

};

#endif
