#ifndef _LIGHT_H
#define _LIGHT_H

#include "Common.h"

class Light
{

public:

	Light();
	~Light();

	void setUpLight(GLuint currentShaderProgram);

	void setAmbientLightColour(vec4 ambientLightColour)
	{
		m_AmbientLightColour = ambientLightColour;
	};
	
	void setDiffuseLightColour(vec4 diffuseLightColour)
	{
		m_DiffuseLightColour = diffuseLightColour;
	};

	void setSpecularLightColour(vec4 specularLightColour)
	{
		m_SpecularLightColour = specularLightColour;
	};

	void setLightDirection(vec3 lightDirection)
	{
		m_LightDirection = lightDirection;
	};

	vec4& getAmbientLightColour()
	{
		return m_AmbientLightColour;
	};

	vec4& getDiffuseLightColour()
	{
		return m_DiffuseLightColour;
	};

	vec4& getSpecularLightColour()
	{
		return m_SpecularLightColour;
	};

	vec3& getLightDirection()
	{
		return m_LightDirection;
	}

private:

	vec4 m_AmbientLightColour;
	vec4 m_DiffuseLightColour;
	vec4 m_SpecularLightColour;

	vec3 m_LightDirection;

protected:

};


#endif