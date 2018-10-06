#include "BoundingBoxShader.h"

Shaders::BoundingBoxShader::BoundingBoxShader()
{

}

Shaders::BoundingBoxShader::BoundingBoxShader(const BoundingBoxShader & other)
{

}

Shaders::BoundingBoxShader::~BoundingBoxShader()
{

}

void Shaders::BoundingBoxShader::BindAttributes()
{
	BindAttrib(0, "position");
	BindAttrib(1, "textureCoords");
	BindAttrib(2, "normal");
}

void Shaders::BoundingBoxShader::GetAllUniforms()
{
	m_location_projectionMatrix = GetUniform("projectionMatrix");
	m_location_transformationMatrix = GetUniform("transformationMatrix");
	m_location_viewMatrix = GetUniform("viewMatrix");
}

void Shaders::BoundingBoxShader::LoadProjectionMatrix(glm::mat4x4 projectionMatrix)
{
	LoadMatrix4(m_location_projectionMatrix, projectionMatrix);
}

void Shaders::BoundingBoxShader::LoadTransformationMatrix(glm::mat4x4 transformationMatrix)
{
	LoadMatrix4(m_location_transformationMatrix, transformationMatrix);
}

void Shaders::BoundingBoxShader::LoadViewMatrix(glm::mat4x4 viewMatrix)
{
	LoadMatrix4(m_location_viewMatrix, viewMatrix);
}