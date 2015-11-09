#ifndef _MESH_H
#define _MESH_H

#include "Common.h"
#include "Component.h"
#include "Vertices.h"

class Mesh:public Component
{
public:
  Mesh();
  ~Mesh();

  void init(Vertex *pVertex, int numVertices, int *pIndices, int numIndices);
  void onPreRender();
  void onRender();
private:
  void bind();
  void destroy();
private:
  GLuint m_VAO;
  GLuint m_VBO;
  GLuint m_EBO;
  int m_numVertices;
  int m_numIndices;

};
#endif
