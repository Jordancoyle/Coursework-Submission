#ifndef _Shader_h
#define _Shader_h

#include "Common.h"

enum SHADER_TYPE
{
VERTEX_SHADER=GL_VERTEX_SHADER,
FRAGMENT_SHADER=GL_FRAGMENT_SHADER
};

GLuint loadShaderFromMemory(const char * pMem, SHADER_TYPE shaderType);

GLuint loadShaderFromFile(const string& filename, SHADER_TYPE shaderType);

bool checkForCompilerErrors(GLuint shaderProgram);

bool checkForLinkErrors(GLuint program);

class Shader
{
public:
	Shader();
	~Shader();

	void loadShaderFromFiles(const string& vsFilename,const string& fsFilename);
	void setVertexShader(GLuint shader);
	void setFragmentShader(GLuint shader);

	bool link();

	GLint getUniformLocation(const string& name);

	void setUniform1i(GLint uniformLocation, int value);
	void setUniform1f(GLint uniformLocation, float value);
	void setUniform2fv(GLint uniformLocation,vec2 &value);
	void setUniform3fv(GLint uniformLocation,vec3 &value);
	void setUniform4fv(GLint uniformLocation,vec4 &value);
	void setUniformMatrix3f(GLint uniformLocation,mat3 &value);
	void setUniformMatrix4f(GLint uniformLocation,mat4 &value);

	void useProgram()
	{
		glUseProgram(m_ShaderProgram);
	}
private:
	GLuint m_ShaderProgram;
	GLuint m_VertexShader;
	GLuint m_FragmentShader;
};

#endif
