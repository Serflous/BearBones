#include "World.h"

Objects::World::World()
{

}

Objects::World::World(const World & other)
{
	m_textures = other.m_textures;
	m_models = other.m_models;
	m_staticEntities = other.m_staticEntities;
}

Objects::World::~World()
{

}

void Objects::World::AddTexture(Objects::Texture texture)
{
	m_textures.push_back(texture);
}

void Objects::World::AddObjModel(Objects::ObjModel model)
{
	m_models.push_back(model);
}

void Objects::World::AddStaticEntity(Objects::StaticEntity entity)
{
	m_staticEntities.push_back(entity);
}

std::vector<Objects::Texture> Objects::World::GetTextures()
{
	return m_textures;
}

std::vector<Objects::ObjModel> Objects::World::GetOBJModels()
{
	return m_models;
}

std::vector<Objects::StaticEntity> Objects::World::GetStaticEntities()
{
	return m_staticEntities;
}