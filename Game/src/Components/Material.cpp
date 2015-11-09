#include "Components/Material.h"
#include "Texture.h"

Material::Material()
{
  m_Type="Material";
  m_DiffuseTexture = 0;
  m_SpecularTexture = 0;
  m_AmbientColour = vec4(0.3, 0.3, 0.3, 1.0);
  m_DiffuseColour = vec4(0.8, 0.8, 0.8, 1.0);
  m_SpecularColour = vec4(1.0, 1.0, 1.0, 1.0);
  m_SpecularPower = 25.0f;
}

Material::~Material()
{

}

void Material::loadDiffuseTexture(const string &filename)
{
	m_DiffuseTexture=loadTextureFromFile(filename);
	glBindTexture(GL_TEXTURE_2D, m_DiffuseTexture);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
	glGenerateMipmap(GL_TEXTURE_2D);
}

void Material::loadSpecularTexture(const string &filename)
{
	m_SpecularTexture = loadTextureFromFile(filename);
	glBindTexture(GL_TEXTURE_2D, m_SpecularTexture);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
	glGenerateMipmap(GL_TEXTURE_2D);
}

void Material::onPreRender()
{
    bind();
}

void Material::bind()
{
  m_pShader->useProgram();

  GLint ambientMaterialLocation=m_pShader->getUniformLocation("ambientMaterial");
  GLint diffuseMaterialLocation=m_pShader->getUniformLocation("diffuseMaterial");
  GLint specularMaterialLocation=m_pShader->getUniformLocation("specularMaterial");
  GLint specularPowerLocation=m_pShader->getUniformLocation("specularPower");
  GLint diffuseTextureLocation = m_pShader->getUniformLocation("diffuseTexture");
  GLint specularTextureLocation = m_pShader->getUniformLocation("specularTexture");

  m_pShader->setUniform4fv(ambientMaterialLocation,m_AmbientColour);
  m_pShader->setUniform4fv(diffuseMaterialLocation,m_DiffuseColour);
  m_pShader->setUniform4fv(specularMaterialLocation,m_SpecularColour);
  m_pShader->setUniform1f(specularPowerLocation,m_SpecularPower);

  glActiveTexture(GL_TEXTURE0);
  glBindTexture(GL_TEXTURE_2D, m_DiffuseTexture);
  m_pShader->setUniform1i(diffuseTextureLocation, 0);

  glActiveTexture(GL_TEXTURE1);
  glBindTexture(GL_TEXTURE_2D, m_SpecularTexture);
  m_pShader->setUniform1i(specularTextureLocation, 1);
}
