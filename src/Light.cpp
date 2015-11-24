#include "Light.h"
#include "Common.h"

Light::Light()
{
	m_AmbientLightColour = vec4(1.0f, 1.0f, 1.0f, 1.0f);
	m_DiffuseLightColour = vec4(1.0f, 1.0f, 1.0f, 1.0f);
	m_SpecularLightColour = vec4(1.0f, 1.0f, 1.0f, 1.0f);

	m_LightDirection = vec3(0.0f, 0.0f, 1.0f);
}

Light::~Light()
{

}

void Light::setUpLight(GLuint currentShaderProgram)
{
	GLint ambientLightColourLocation = glGetUniformLocation(currentShaderProgram, "ambientLightColour");
	glUniform4fv(ambientLightColourLocation, 1, glm::value_ptr(m_AmbientLightColour));

	GLint diffuseLightColourLocation = glGetUniformLocation(currentShaderProgram, "diffuseLightColour");
	glUniform4fv(diffuseLightColourLocation, 1, glm::value_ptr(m_DiffuseLightColour));

	GLint lightDirectionLocation = glGetUniformLocation(currentShaderProgram, "lightDirection");
	glUniform3fv(lightDirectionLocation, 1, glm::value_ptr(m_LightDirection));

	GLint specularLightColourLocation = glGetUniformLocation(currentShaderProgram, "specularLightColour");
	glUniform4fv(specularLightColourLocation, 1, glm::value_ptr(m_SpecularLightColour));

};