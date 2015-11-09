#include "Components/Transform.h"
#include "GameObject.h"

void Transform::onUpdate()
{
  //build the matrices
  //get parent model material
  mat4 parentModel(1.0f);
  if (m_pOwner)
  {
    GameObject *pParent=m_pOwner->getParent();
    if (pParent)
    {
      shared_ptr<Transform> t=static_pointer_cast<Transform>(pParent->getComponent("Transform"));
      parentModel=t->getModelMatrix();
    }
  }
  m_TranlationMatrix=translate(mat4(1.0f),m_Position);
  m_ScaleMatrix=scale(mat4(1.0f),m_Scale);

  m_RotationalMatrix=rotate(mat4(1.0f),m_Rotation.x,vec3(1.0f,0.0f,0.0f))*
  rotate(mat4(1.0f),m_Rotation.y,vec3(0.0f,1.0f,0.0f))*
  rotate(mat4(1.0f),m_Rotation.z,vec3(0.0f,0.0f,1.0f));

  m_ModelMatrix=m_ScaleMatrix*m_RotationalMatrix*m_TranlationMatrix;
  m_ModelMatrix*=parentModel;
  
}
