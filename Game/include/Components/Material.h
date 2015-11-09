#ifndef _MATERIAL_H
#define _MATERIAL_H

#include "Common.h"
#include "Component.h"
#include "Shader.h"

class Material:public Component
{
public:
  Material();
  virtual ~Material();

  void onPreRender();

  void setAmbientColour(const vec4& colour)
  {
    m_AmbientColour=colour;
  };

  void setDiffuseColour(const vec4& colour)
  {
    m_DiffuseColour=colour;
  };

  void setSpecularColour(const vec4& colour)
  {
    m_SpecularColour=colour;
  };

  void setSpecularPower(float power)
  {
    m_SpecularPower=power;
  };

  void setShader(shared_ptr<Shader> shader)
  {
    m_pShader=shader;
  };

  void loadDiffuseTexture(const string &filename);
  void loadSpecularTexture(const string &filename);

  shared_ptr<Shader> getShader()
  {
    return m_pShader;
  }

protected:
  virtual void bind();
protected:
  vec4 m_AmbientColour;
  vec4 m_DiffuseColour;
  vec4 m_SpecularColour;
  float m_SpecularPower;
  GLuint m_DiffuseTexture;
  GLuint m_SpecularTexture;
  shared_ptr<Shader> m_pShader;
};

#endif
