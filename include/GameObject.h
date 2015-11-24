#ifndef _GAMEOBJECT_H
#define _GAMEOBJECT_H

#include "Common.h"
#include "Vertices.h"


class GameObject
{
public:

	GameObject();
	~GameObject();

	void update();

	void createBuffer(Vertex *pVerts, int numVerts, int *pindices, int numIndices);
	void loadShader(const string& vsFilename, const string& fsFilename);
	void setUpGameObjectMaterial(GLuint currentShaderProgram);

	GLuint getShaderProgram()
	{
		return m_ShaderProgram;
	};

	GLuint getVertexArrayObject()
	{
		return m_VAO;
	};

	int getNumberOfIndices()
	{
		return m_NoOfIndices;
	};

	mat4& getModelMatrix()
	{
		return m_ModelMatrix;
	};

	void setPosition(const vec3& position)
	{
		m_Position = position;
	};

	void setScale(const vec3& scale)
	{
		m_Scale = scale;
	};

	void setRotation(const vec3& rotation)
	{
		m_Rotation = rotation;
	};

	GameObject * getParent()
	{
		return m_ParentGameObject;
	};

	int getNumberOfChildren()
	{
		return  m_ChildGameObjects.size();
	};

	void addChild(shared_ptr<GameObject> child)
	{
		child->m_ParentGameObject = this;
		m_ChildGameObjects.push_back(child);
	};

	shared_ptr<GameObject> getChild(int i)
	{
		return m_ChildGameObjects.at(i);
	}

private:
	GLuint m_VBO;
	GLuint m_EBO;
	GLuint m_VAO;
	GLuint m_ShaderProgram;
	int m_NoOfVertices;
	int m_NoOfIndices;

	mat4 m_ModelMatrix;
	vec3 m_Position;
	vec3 m_Rotation;
	vec3 m_Scale;

	vec4 m_AmbientMaterial;
	vec4 m_DiffuseMaterial;
	vec4 m_SpecularMaterial;
	float m_SpecularPower;

	GameObject * m_ParentGameObject;
	vector <shared_ptr<GameObject>> m_ChildGameObjects;

protected:


};


#endif