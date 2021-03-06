#include "Entity.h"

Objects::Entity::Entity()
{
	m_position = glm::vec3(0, 0, 0);
	m_rotation = glm::vec3(0, 0, 0);
	m_scale = glm::vec3(1, 1, 1);
}

Objects::Entity::Entity(const Entity & other)
{
	m_model = other.m_model;
	m_position = other.m_position;
	m_rotation = other.m_rotation;
	m_scale = other.m_scale;
}

Objects::Entity::~Entity()
{

}

void Objects::Entity::SetModel(std::shared_ptr<Objects::ModelBase> model)
{
	m_model = model;
}

void Objects::Entity::SetPosition(glm::vec3 position)
{
	m_position = position;
}

void Objects::Entity::SetRotation(glm::vec3 rotation)
{
	m_rotation = rotation;
}

void Objects::Entity::SetScale(glm::vec3 scale)
{
	m_scale = scale;
}

std::shared_ptr<Objects::ModelBase> Objects::Entity::GetModel()
{
	return m_model;
}

glm::vec3 Objects::Entity::GetPosition()
{
	return m_position;
}

glm::vec3 Objects::Entity::GetRotation()
{
	return m_rotation;
}

glm::vec3 Objects::Entity::GetScale()
{
	return m_scale;
}

std::shared_ptr<Collision::BoundingVolume> Objects::Entity::GetBoundingVolume()
{
	return m_boundingVolume;
}

void Objects::Entity::SetAffordances(std::string key, double value)
{
	m_affordances[key] = value;
}

void Objects::Entity::SetAffordanceMap(std::map<std::string, double> map)
{
	m_affordances = map;
}

std::map<std::string, double> Objects::Entity::GetAffordances()
{
	return m_affordances;
}