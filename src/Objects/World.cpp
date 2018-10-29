#include "World.h"

Objects::World::World()
{
	m_textures = std::make_shared<std::vector<std::shared_ptr<Texture>>>();
	m_objModels = std::make_shared<std::vector<std::shared_ptr<ObjModel>>>();
	m_primitiveModels = std::make_shared<std::vector<std::shared_ptr<PrimitiveModel>>>();
	m_staticEntities = std::make_shared<std::vector<std::shared_ptr<StaticEntity>>>();
	m_rigidBodies = std::make_shared<std::vector<std::shared_ptr<Objects::RigidBody>>>();
	m_terrains = std::make_shared<std::vector<std::shared_ptr<Objects::Terrain>>>();
	m_debugObjects = std::make_shared<std::vector<std::shared_ptr<Entity>>>();
	m_gui = nullptr;
}

Objects::World::World(const World & other)
{
	m_textures = other.m_textures;
	m_objModels = other.m_objModels;
	m_primitiveModels = other.m_primitiveModels;
	m_staticEntities = other.m_staticEntities;
	m_rigidBodies = other.m_rigidBodies;
	m_terrains = other.m_terrains;
	m_debugObjects = other.m_debugObjects;
	m_gui = other.m_gui;
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
	m_objModels->push_back(model);
}

void Objects::World::AddPrimitiveModel(std::shared_ptr<PrimitiveModel> model)
{
	m_primitiveModels->push_back(model);
}

void Objects::World::AddStaticEntity(std::shared_ptr<Objects::StaticEntity> entity)
{
	m_staticEntities->push_back(entity);
}

void Objects::World::AddRigidBody(std::shared_ptr<Objects::RigidBody> entity)
{
	m_rigidBodies->push_back(entity);
}

void Objects::World::AddTerrain(std::shared_ptr<Objects::Terrain> terrain)
{
	m_terrains->push_back(terrain);
}

void Objects::World::AddDebugObject(std::shared_ptr<Objects::Entity> model)
{
	m_debugObjects->push_back(model);
}

void Objects::World::AddNPC(std::shared_ptr<NPC> npc)
{
	m_npcs->push_back(npc);
}

void Objects::World::SetGUI(std::shared_ptr<Objects::GUI> gui)
{
	m_gui = gui;
}

std::shared_ptr<std::vector<std::shared_ptr<Objects::Texture>>> Objects::World::GetTextures()
{
	return m_textures;
}

std::shared_ptr<std::vector<std::shared_ptr<Objects::ObjModel>>> Objects::World::GetOBJModels()
{
	return m_objModels;
}

std::shared_ptr<std::vector<std::shared_ptr<Objects::PrimitiveModel>>> Objects::World::GetPrimitiveModels()
{
	return m_primitiveModels;
}

std::shared_ptr<std::vector<std::shared_ptr<Objects::StaticEntity>>> Objects::World::GetStaticEntities()
{
	return m_staticEntities;
}

std::shared_ptr<std::vector<std::shared_ptr<Objects::RigidBody>>> Objects::World::GetRigidBodies()
{
	return m_rigidBodies;
}

std::shared_ptr<std::vector<std::shared_ptr<Objects::Terrain>>> Objects::World::GetTerrains()
{
	return m_terrains;
}

std::shared_ptr<std::vector<std::shared_ptr<Objects::Entity>>> Objects::World::GetDebugObjects()
{
	return m_debugObjects;
}

std::shared_ptr<Objects::GUI> Objects::World::GetGUI()
{
	return m_gui;
}

void Objects::World::Update()
{

}