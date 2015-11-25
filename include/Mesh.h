#ifndef _MESH_H
#define _MESH_H

#include "Vertices.h"
#include "Common.h"

class Mesh
{
public:

	Mesh();
	~Mesh();
	void update();
	void create(Vertex *pVerts, int numVerts, int *pindices, int numIndices);

	GLuint getVertexArrayObject()
	{
		return m_VAO;
	}; 
	
	int getNumberOfIndices()
	{
		return m_NoOfIndices;
	};

	int getNumberOfVertices()
	{
		return m_NoOfVertices;
	};

private:
	GLuint m_VBO;
	GLuint m_EBO;
	GLuint m_VAO;

	int m_NoOfVertices;
	int m_NoOfIndices;

protected:
};

#endif