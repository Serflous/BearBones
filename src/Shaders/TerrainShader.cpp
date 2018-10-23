#include "TerrainShader.h"

Shaders::TerrainShader::TerrainShader()
{

}

Shaders::TerrainShader::TerrainShader(TerrainShader & other)
{

}

Shaders::TerrainShader::~TerrainShader()
{

}

void Shaders::TerrainShader::BindAttributes()
{

}

void Shaders::TerrainShader::GetAllUniforms()
{
	m_location_projectionMatrix = GetUniform("projectionMatrix");
	m_location_transformationMatrix = GetUniform("transformationMatrix");
	m_location_viewMatrix = GetUniform("viewMatrix");
}

void Shaders::TerrainShader::LoadProjectionMatrix(glm::mat4x4 projectionMatrix)
{
	LoadMatrix4(m_location_projectionMatrix, projectionMatrix);
}

void Shaders::TerrainShader::LoadTransformationMatrix(glm::mat4x4 transformationMatrix)
{
	LoadMatrix4(m_location_transformationMatrix, transformationMatrix);
}

void Shaders::TerrainShader::LoadViewMatrix(glm::mat4x4 viewMatrix)
{
	LoadMatrix4(m_location_viewMatrix, viewMatrix);
}