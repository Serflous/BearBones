#include "TerrainTextureCollection.h"

Objects::TerrainTextureCollection::TerrainTextureCollection()
{
	m_textures = std::vector<std::shared_ptr<Texture>>(3);
}

Objects::TerrainTextureCollection::TerrainTextureCollection(const TerrainTextureCollection & other)
{
	m_baseTexture = other.m_baseTexture;
	m_textures = other.m_textures;
}

Objects::TerrainTextureCollection::~TerrainTextureCollection()
{

}

void Objects::TerrainTextureCollection::SetBaseTexture(std::shared_ptr<Texture> texture)
{
	m_baseTexture = texture;
}

void Objects::TerrainTextureCollection::SetTexture(int idx, std::shared_ptr<Texture> texture)
{
	m_textures[idx] = texture;
}

std::shared_ptr<Objects::Texture> Objects::TerrainTextureCollection::GetBaseTexture()
{
	return m_baseTexture;
}

std::shared_ptr<Objects::Texture> Objects::TerrainTextureCollection::GetTextureAt(int idx)
{
	return m_textures[idx];
}