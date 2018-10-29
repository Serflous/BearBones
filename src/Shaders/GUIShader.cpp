#include "GUIShader.h"

Shaders::GUIShader::GUIShader()
{
	m_location_transformationMatrix = 0;
}

Shaders::GUIShader::GUIShader(const GUIShader & other)
{
	m_location_transformationMatrix = other.m_location_transformationMatrix;
}

Shaders::GUIShader::~GUIShader()
{

}

void Shaders::GUIShader::BindAttributes()
{
	BindAttrib(0, "position");
}

void Shaders::GUIShader::GetAllUniforms()
{
	m_location_transformationMatrix = GetUniform("transformationMatrix");
}

void Shaders::GUIShader::LoadTransformationMatrix(glm::mat4x4 transformationMatrix)
{
	LoadMatrix4(m_location_transformationMatrix, transformationMatrix);
}