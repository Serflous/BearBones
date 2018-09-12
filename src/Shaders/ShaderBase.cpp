#include "ShaderBase.h"

Shaders::ShaderBase::ShaderBase()
{

}

Shaders::ShaderBase::ShaderBase(const ShaderBase & other)
{

}

Shaders::ShaderBase::~ShaderBase()
{

}

void Shaders::ShaderBase::Start()
{
	glUseProgram(m_programId);
}

void Shaders::ShaderBase::Stop()
{
	glUseProgram(0);
}

void Shaders::ShaderBase::SetProgramID(int id)
{
	m_programId = id;
}

void Shaders::ShaderBase::SetVertexShaderID(int id)
{
	m_vertexShaderId = id;
}

void Shaders::ShaderBase::SetFragmentShaderID(int id)
{
	m_fragmentShaderId = id;
}

int Shaders::ShaderBase::GetProgramID()
{
	return m_programId;
}

int Shaders::ShaderBase::GetVertexShaderID()
{
	return m_vertexShaderId;
}

int Shaders::ShaderBase::GetFragmentShaderID()
{
	return m_fragmentShaderId;
}

void Shaders::ShaderBase::BindAttrib(int attrib, const char * name)
{
	glBindAttribLocation(m_programId, attrib, name);
}

GLuint Shaders::ShaderBase::GetUniform(const char * name)
{
	return glGetUniformLocation(m_programId, name);
}

void Shaders::ShaderBase::LoadFloat(GLuint location, float value)
{
	glUniform1f(location, value);
}

void Shaders::ShaderBase::LoadInt(GLuint location, int value)
{
	glUniform1i(location, value);
}

void Shaders::ShaderBase::LoadUInt(GLuint location, unsigned int value)
{
	glUniform1ui(location, value);
}

void Shaders::ShaderBase::LoadVec3(GLuint location, glm::vec3 value)
{
	glUniform3f(location, value.x, value.y, value.z);
}

void Shaders::ShaderBase::LoadBoolean(GLuint location, bool value)
{
	glUniform1f(location, (value ? 1.0f : 0.0f));
}

void Shaders::ShaderBase::LoadMatrix4(GLuint location, glm::mat4x4 value)
{
	glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(value));
}