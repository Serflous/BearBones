#include "ObjModel.h"

Objects::ObjModel::ObjModel()
{
	m_vaoId = 0;
	m_vertexCount = 0;
	m_modelHeight = 0;
}

Objects::ObjModel::ObjModel(const ObjModel & other)
{
	m_vaoId = other.m_vaoId;
	m_vertexCount = other.m_vertexCount;
	m_modelHeight = other.m_modelHeight;
	m_texture = other.m_texture;
	m_verticies = other.m_verticies;
	m_uvs = other.m_uvs;
	m_normals = other.m_normals;
}

Objects::ObjModel::~ObjModel()
{

}

void Objects::ObjModel::SetModelHeight(double height)
{
	m_modelHeight = height;
}

void Objects::ObjModel::SetTexture(std::shared_ptr<Texture> tex)
{
	m_texture = tex;
}

void Objects::ObjModel::SetUVs(std::vector<glm::vec2> uvs)
{
	m_uvs = uvs;
}

void Objects::ObjModel::SetNormals(std::vector<glm::vec3> norms)
{
	m_normals = norms;
}

double Objects::ObjModel::GetModelHeight()
{
	return m_modelHeight;
}

std::vector<glm::vec2> Objects::ObjModel::GetUVs()
{
	return m_uvs;
}

std::vector<glm::vec3> Objects::ObjModel::GetNormals()
{
	return m_normals;
}

std::shared_ptr<Objects::Texture> Objects::ObjModel::GetTexture()
{
	return m_texture;
}