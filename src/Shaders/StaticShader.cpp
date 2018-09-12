#include "StaticShader.h"

Shaders::StaticShader::StaticShader()
{

}

Shaders::StaticShader::StaticShader(const StaticShader & other)
{

}

Shaders::StaticShader::~StaticShader()
{

}

void Shaders::StaticShader::BindAttributes()
{
	BindAttrib(0, "position");
	BindAttrib(1, "textureCoords");
	BindAttrib(2, "normal");
}

void Shaders::StaticShader::GetAllUniforms()
{
	m_location_projectionMatrix = GetUniform("projectionMatrix");
	m_location_transformationMatrix = GetUniform("transformationMatrix");
	m_location_viewMatrix = GetUniform("viewMatrix");
}

void Shaders::StaticShader::LoadProjectionMatrix(glm::mat4x4 projectionMatrix)
{
	LoadMatrix4(m_location_projectionMatrix, projectionMatrix);
}

void Shaders::StaticShader::LoadTransformationMatrix(glm::mat4x4 transformationMatrix)
{
	LoadMatrix4(m_location_transformationMatrix, transformationMatrix);
}

void Shaders::StaticShader::LoadViewMatrix(glm::mat4x4 viewMatrix)
{
	LoadMatrix4(m_location_viewMatrix, viewMatrix);
}