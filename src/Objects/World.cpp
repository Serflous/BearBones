#include "World.h"

Objects::World::World()
{
	m_textures = std::make_shared<std::vector<std::shared_ptr<Texture>>>();
	m_models = std::make_shared<std::vector<std::shared_ptr<ObjModel>>>();
	m_staticEntities = std::make_shared<std::vector<std::shared_ptr<StaticEntity>>>();
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

void Objects::World::AddTexture(std::shared_ptr<Objects::Texture> texture)
{
	m_textures->push_back(texture);
}

void Objects::World::AddObjModel(std::shared_ptr<Objects::ObjModel> model)
{
	m_models->push_back(model);
}

void Objects::World::AddStaticEntity(std::shared_ptr<Objects::StaticEntity> entity)
{
	m_staticEntities->push_back(entity);
}

void Objects::World::AddRigidBody(std::shared_ptr<Objects::RigidBody> entity)
{
	m_rigidBodies->push_back(entity);
}

std::shared_ptr<std::vector<std::shared_ptr<Objects::Texture>>> Objects::World::GetTextures()
{
	return m_textures;
}

std::shared_ptr<std::vector<std::shared_ptr<Objects::ObjModel>>> Objects::World::GetOBJModels()
{
	return m_models;
}

std::shared_ptr<std::vector<std::shared_ptr<Objects::StaticEntity>>> Objects::World::GetStaticEntities()
{
	return m_staticEntities;
}

std::shared_ptr<std::vector<std::shared_ptr<Objects::RigidBody>>> Objects::World::GetRigidBodies()
{
	return m_rigidBodies;
}