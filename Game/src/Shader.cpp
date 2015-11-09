#include "Shader.h"

//Load it from a memory buffer
GLuint loadShaderFromMemory(const char * pMem, SHADER_TYPE shaderType)
{
  GLuint program = glCreateShader(shaderType);
  glShaderSource(program, 1, &pMem, NULL);
  glCompileShader(program);
  return program;
}

//Load Shader from File
GLuint loadShaderFromFile(const std::string& filename, SHADER_TYPE shaderType)
{
  string fileContents;
  ifstream file;
  file.open(filename.c_str(), std::ios::in);
  if (!file)
  {
	  cout << "File could not be loaded" << endl;
    return 0;
  }

  //calculate file size
  if (file.good())
  {
    file.seekg(0, std::ios::end);
    unsigned long len = file.tellg();
    file.seekg(std::ios::beg);
    if (len == 0)
    {
      std::cout << "File has no contents " << std::endl;
      return 0;
    }

    fileContents.resize(len);
    file.read(&fileContents[0], len);
    file.close();
    GLuint program = loadShaderFromMemory(fileContents.c_str(), shaderType);
    return program;
  }

  return 0;
}

bool checkForCompilerErrors(GLuint shaderProgram)
{
  GLint isCompiled = 0;
  glGetShaderiv(shaderProgram, GL_COMPILE_STATUS, &isCompiled);
  if (isCompiled == GL_FALSE)
  {
    GLint maxLength = 0;
    glGetShaderiv(shaderProgram, GL_INFO_LOG_LENGTH, &maxLength);
    //The maxLength includes the NULL character
    string infoLog;
    infoLog.resize(maxLength);
    glGetShaderInfoLog(shaderProgram, maxLength, &maxLength, &infoLog[0]);
    cout << "Shader not compiled " << infoLog << endl;
    //We don't need the shader anymore.
    glDeleteShader(shaderProgram);
    return true;
  }

  return false;
}

bool checkForLinkErrors(GLuint program)
{
  GLint isLinked = 0;
  glGetProgramiv(program, GL_LINK_STATUS, &isLinked);
  if (isLinked == GL_FALSE) {
    GLint maxLength = 0;
    glGetProgramiv(program, GL_INFO_LOG_LENGTH, &maxLength);
    //The maxLength includes the NULL character
    string infoLog;
    glGetProgramInfoLog(program, maxLength, &maxLength, &infoLog[0]);
    cout << "Shader not linked " << infoLog << endl;
    //We don't need the shader anymore.
    glDeleteProgram(program);
    return true;
  }
  return false;
}

Shader::Shader()
{
	m_ShaderProgram=0;
	m_VertexShader=0;
	m_FragmentShader=0;
}

Shader::~Shader()
{
	glDeleteProgram(m_ShaderProgram);
}

void Shader::setVertexShader(GLuint shader)
{
	checkForCompilerErrors(shader);
	m_VertexShader = shader;
}

void Shader::setFragmentShader(GLuint shader)
{
	checkForCompilerErrors(shader);
	m_FragmentShader = shader;
}

void Shader::loadShaderFromFiles(const string& vsFilename,const string& fsFilename)
{
  GLuint vertexShader=loadShaderFromFile(vsFilename,VERTEX_SHADER);
  setVertexShader(vertexShader);

  GLuint fragmentShader=loadShaderFromFile(fsFilename,FRAGMENT_SHADER);
  setFragmentShader(fragmentShader);
}

bool Shader::link()
{
	if (m_VertexShader == 0 || m_FragmentShader == 0)
	{
		cout << "Shaders not set" << endl;
		return false;
	}

	m_ShaderProgram = glCreateProgram();
	glAttachShader(m_ShaderProgram, m_VertexShader);
	glAttachShader(m_ShaderProgram, m_FragmentShader);

	glLinkProgram(m_ShaderProgram);
	if (checkForLinkErrors(m_ShaderProgram))
	{
		glDeleteShader(m_VertexShader);
		glDeleteShader(m_FragmentShader);
		return false;
	}

	glBindAttribLocation(m_ShaderProgram, 0, "vertexPosition");
	glBindAttribLocation(m_ShaderProgram, 1, "vertexColour");
	glBindAttribLocation(m_ShaderProgram, 2, "vertexTexCoords");
	glBindAttribLocation(m_ShaderProgram, 3, "vertexNormal");

	glDeleteShader(m_VertexShader);
	glDeleteShader(m_FragmentShader);
	return true;

}

GLint Shader::getUniformLocation(const string& name)
{
  return glGetUniformLocation(m_ShaderProgram,name.c_str());
}

void Shader::setUniform1i(GLint uniformLocation, int value)
{
  glUniform1i(uniformLocation,value);
}

void Shader::setUniform1f(GLint uniformLocation, float value)
{
  glUniform1f(uniformLocation,value);
}

void Shader::setUniform2fv(GLint uniformLocation,vec2 &value)
{
  glUniform2fv(uniformLocation,1,value_ptr(value));
}

void Shader::setUniform3fv(GLint uniformLocation,vec3 &value)
{
  glUniform3fv(uniformLocation,1,value_ptr(value));
}

void Shader::setUniform4fv(GLint uniformLocation,vec4 &value)
{
  glUniform4fv(uniformLocation,1,value_ptr(value));
}

void Shader::setUniformMatrix3f(GLint uniformLocation,mat3 &value)
{
  glUniformMatrix3fv(uniformLocation,1,GL_FALSE,value_ptr(value));
}

void Shader::setUniformMatrix4f(GLint uniformLocation,mat4 &value)
{
  glUniformMatrix4fv(uniformLocation,1,GL_FALSE,value_ptr(value));
}
