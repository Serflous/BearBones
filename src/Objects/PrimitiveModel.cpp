#include "PrimitiveModel.h"

Objects::PrimitiveModel::PrimitiveModel()
{

}

Objects::PrimitiveModel::PrimitiveModel(const PrimitiveModel & other)
{
	m_colour = other.m_colour;
	m_vaoId = other.m_vaoId;
	m_vertexCount = other.m_vertexCount;
	m_verticies = other.m_verticies;
}

Objects::PrimitiveModel::~PrimitiveModel()
{

}

void Objects::PrimitiveModel::SetColour(glm::vec3 colour)
{
	m_colour = colour;
}

glm::vec3 Objects::PrimitiveModel::GetColour()
{
	return m_colour;
}