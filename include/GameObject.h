#ifndef _GAMEOBJECT_H
#define _GAMEOBJECT_H

#include "Common.h"
#include "Vertices.h"
#include "Mesh.h"
#include "Material.h"


class GameObject
{
public:

	GameObject();
	~GameObject();

	void update();

	void loadShader(const string& vsFilename, const string& fsFilename);
	void loadDiffuseMap(const string& filename);
	void setUpGameObjectMaterial();
	void createBuffer(Vertex * pVerts, int numVerts, int *pindices, int numIndices);

	GLuint getVertexArrayObject()
	{
		return m_Mesh->getVertexArrayObject();
	};

	int getNumberOfIndices()
	{
		return m_Mesh->getNumberOfIndices();
	};

	int getNumberOfVertices()
	{
		return m_Mesh->getNumberOfVertices();
	};


	GLuint getShaderProgram()
	{
		return m_Material->getShaderProgram();
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

	vec4& getAmbientMaterial()
	{
		return m_Material->getAmbientMaterial();
	};

	vec4& getDiffuseMaterial()
	{
		return m_Material->getDiffuseMaterial();
	};

	vec4& getSpecularMaterial()
	{
		return m_Material->getSpecularMaterial();
	};

	float getSpecularPower()
	{
		return m_Material->getSpecularPower();
	};

	GLuint getDiffuseMap()
	{
		return m_Material->getDiffuseMap();
	};

private:
	mat4 m_ModelMatrix;
	vec3 m_Position;
	vec3 m_Rotation;
	vec3 m_Scale;

	GameObject * m_ParentGameObject;
	vector <shared_ptr<GameObject>> m_ChildGameObjects;

	shared_ptr<Mesh> m_Mesh;
	shared_ptr<Material> m_Material;

protected:


};


#endif