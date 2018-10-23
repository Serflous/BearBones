#include "ModelBase.h"

Objects::ModelBase::ModelBase()
{
	m_vaoId = 0;
	m_vertexCount = 0;
}

Objects::ModelBase::ModelBase(const ModelBase & other)
{
	m_vaoId = other.m_vaoId;
	m_vertexCount = other.m_vertexCount;
	m_verticies = other.m_verticies;
}

Objects::ModelBase::~ModelBase()
{

}

void Objects::ModelBase::SetVAOID(int vaoId)
{
	m_vaoId = vaoId;
}

void Objects::ModelBase::SetVertexCount(int vertexCount)
{
	m_vertexCount = vertexCount;
}

void Objects::ModelBase::SetVerticies(std::vector<glm::vec3> verts)
{
	m_verticies = verts;
}

int Objects::ModelBase::GetVAOID()
{
	return m_vaoId;
}

int Objects::ModelBase::GetVertexCount()
{
	return m_vertexCount;
}

std::vector<glm::vec3> Objects::ModelBase::GetVerticies()
{
	return m_verticies;
}