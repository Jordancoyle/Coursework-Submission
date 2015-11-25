#include "Mesh.h"

Mesh::Mesh()
{
	m_VBO = 0;
	m_EBO = 0;
	m_VAO = 0;

	m_NoOfVertices = 0;
	m_NoOfIndices = 0;
}

Mesh::~Mesh()
{
	glDeleteBuffers(1, &m_EBO);
	glDeleteBuffers(1, &m_VBO);
	glDeleteVertexArrays(1, &m_VAO);
}

void Mesh::create(Vertex *pVerts, int numVerts, int *pindices, int numIndices)
{
	m_NoOfVertices = numVerts;
	m_NoOfIndices = numIndices;

	//Generate Vertex Array
	glGenVertexArrays(1, &m_VAO);
	glBindVertexArray(m_VAO);
	glGenBuffers(1, &m_VBO);
	glBindBuffer(GL_ARRAY_BUFFER, m_VBO);

	glBufferData(GL_ARRAY_BUFFER, numVerts*sizeof(Vertex), pVerts, GL_STATIC_DRAW);

	//Generate Element buffer object
	glGenBuffers(1, &m_EBO);
	//Make the EBO active
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_EBO);
	//Copy Index data to the EBO
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, numIndices*sizeof(int), pindices, GL_STATIC_DRAW);

	//Tell the shader that 0 is the position element
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), NULL);

	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void**)(sizeof(vec3)));

	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void**)(sizeof(vec3) + sizeof(vec4)));

	glEnableVertexAttribArray(3);
	glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void**)(sizeof(vec3) + sizeof(vec4) + sizeof(vec2)));

}