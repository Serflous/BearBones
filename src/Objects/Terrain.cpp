#include "Terrain.h"

Objects::Terrain::Terrain()
{
	m_vaoId = 0;
	m_vertexCount = 0;
	m_terrainHeightData = nullptr;
	m_size = 0;
	m_scale = glm::vec3(0, 0, 0);
	m_position = glm::vec3(0, 0, 0);
}

Objects::Terrain::Terrain(const Terrain & other)
{
	m_vaoId = other.m_vaoId;
	m_vertexCount = other.m_vertexCount;
	m_terrainHeightData = other.m_terrainHeightData;
	m_size = other.m_size;
	m_scale = other.m_scale;
	m_terrainCollection = other.m_terrainCollection;
	m_position = other.m_position;
}

Objects::Terrain::~Terrain()
{

}

void Objects::Terrain::SetVaoID(int vaoId)
{
	m_vaoId = vaoId;
}

void Objects::Terrain::SetVertexCount(int vertexCount)
{
	m_vertexCount = vertexCount;
}

void Objects::Terrain::SetTerrainHeightData(unsigned char * data)
{
	m_terrainHeightData = data;
}

void Objects::Terrain::SetSize(int size)
{
	m_size = size;
}

void Objects::Terrain::SetPosition(glm::vec3 position)
{
	m_position = position;
}

void Objects::Terrain::SetScale(glm::vec3 scale)
{
	m_scale = scale;
}

void Objects::Terrain::SetTerrainTextureCollection(std::shared_ptr<TerrainTextureCollection> collection)
{
	m_terrainCollection = collection;
}

int Objects::Terrain::GetVaoID()
{
	return m_vaoId;
}

int Objects::Terrain::GetVertexCount()
{
	return m_vertexCount;
}

unsigned char * Objects::Terrain::GetTerrainHeightData()
{
	return m_terrainHeightData;
}

int Objects::Terrain::GetSize()
{
	return m_size;
}

glm::vec3 Objects::Terrain::GetPosition()
{
	return m_position;
}

glm::vec3 Objects::Terrain::GetScale()
{
	return m_scale;
}

std::shared_ptr<Objects::TerrainTextureCollection> Objects::Terrain::GetTerrainTextureCollection()
{
	return m_terrainCollection;
}

float Objects::Terrain::GetHeight(int x, int z)
{
	if (InBounds(x, z))
	{
		return (float)m_terrainHeightData[z * m_size + x];
	}
}

float Objects::Terrain::GetRelativeHeight(float x, float z)
{
	double fract = 0;
	float xPercentage = modf(x, &fract);
	float zPercentage = modf(z, &fract);

	float sideOneHeightX = GetHeight(floor(x), floor(z));
	float sideOneHeightZ = GetHeight(ceil(x), floor(z));
	float sideOneLerped = (1 - xPercentage) * sideOneHeightX + xPercentage * sideOneHeightZ;

	float sideTwoHeightX = GetHeight(floor(x), ceil(z));
	float sideTwoHeightZ = GetHeight(ceil(x), ceil(z));
	float sideTwoLerped = (1 - xPercentage) * sideTwoHeightX + xPercentage * sideTwoHeightZ;

	return (1 - zPercentage) * sideOneLerped + zPercentage * sideTwoLerped;
}

bool Objects::Terrain::InBounds(int x, int z)
{
	return z * m_size + x <= m_size * m_size;
}