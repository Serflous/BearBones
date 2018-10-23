#include "PrimitiveShader.h"

Shaders::PrimitiveShader::PrimitiveShader()
{
	m_location_projectionMatrix = 0;
	m_location_transformationMatrix = 0;
	m_location_viewMatrix = 0;
	m_location_colour = 0;
}

Shaders::PrimitiveShader::PrimitiveShader(const PrimitiveShader & other)
{
	m_location_projectionMatrix = other.m_location_projectionMatrix;
	m_location_transformationMatrix = other.m_location_transformationMatrix;
	m_location_viewMatrix = other.m_location_viewMatrix;
	m_location_colour = other.m_location_colour;
}

Shaders::PrimitiveShader::~PrimitiveShader()
{

}

void Shaders::PrimitiveShader::BindAttributes()
{
	BindAttrib(0, "positions");
}

void Shaders::PrimitiveShader::GetAllUniforms()
{
	m_location_projectionMatrix = GetUniform("projectionMatrix");
	m_location_transformationMatrix = GetUniform("transformationMatrix");
	m_location_viewMatrix = GetUniform("viewMatrix");
	m_location_colour = GetUniform("primColour");
}

void Shaders::PrimitiveShader::LoadProjectionMatrix(glm::mat4x4 projectionMatrix)
{
	LoadMatrix4(m_location_projectionMatrix, projectionMatrix);
}

void Shaders::PrimitiveShader::LoadTransformationMatrix(glm::mat4x4 transformationMatrix)
{
	LoadMatrix4(m_location_transformationMatrix, transformationMatrix);
}

void Shaders::PrimitiveShader::LoadViewMatrix(glm::mat4x4 viewMatrix)
{
	LoadMatrix4(m_location_viewMatrix, viewMatrix);
}

void Shaders::PrimitiveShader::LoadColour(glm::vec3 colour)
{
	LoadVec3(m_location_colour, colour);
}