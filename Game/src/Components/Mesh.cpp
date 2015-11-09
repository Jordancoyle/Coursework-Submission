#include "Components/Mesh.h"

Mesh::Mesh()
{
  m_VAO=0;
  m_VBO=0;
  m_EBO=0;
  m_Type="Mesh";
}

Mesh::~Mesh()
{
  destroy();
}

void Mesh::init(Vertex *pVertex, int numVertices, int *pIndices, int numIndices)
{
    glGenVertexArrays(1,&m_VAO);
    glBindVertexArray(m_VAO);

	glGenBuffers(1, &m_VBO); 
	glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
    glBufferData(GL_ARRAY_BUFFER, numVertices * sizeof(Vertex),pVertex, GL_STATIC_DRAW);

    glGenBuffers(1,&m_EBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, numIndices * sizeof(int),pIndices, GL_STATIC_DRAW);

    //describe vertices
    glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), NULL);
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)12);
    glEnableVertexAttribArray(3);
	glVertexAttribPointer(3, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)28);



    m_numVertices=numVertices;
    m_numIndices=numIndices;
	glBindVertexArray(0);
}

void Mesh::onPreRender()
{
  bind();
}

void Mesh::bind()
{
  glBindVertexArray(m_VAO);
}

void Mesh::onRender()
{
  glDrawElements(GL_TRIANGLES, m_numIndices, GL_UNSIGNED_INT, 0);
}

void Mesh::destroy()
{
  glDeleteBuffers(1,&m_EBO);
  glDeleteBuffers(1,&m_VBO);
  glDeleteVertexArrays(1,&m_VAO);
}
