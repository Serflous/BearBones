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

void Objects::Entity::SetModel(std::shared_ptr<Objects::ObjModel> model)
{
	m_model = model;
}

void Objects::Entity::SetPosition(glm::vec3 position, bool updateBB)
{
	m_position = position;
	if (updateBB)
	{
		m_collisionObject->getWorldTransform().setOrigin(btVector3(position.x, position.y, position.z));
	}
}

void Objects::Entity::SetRotation(glm::vec3 rotation, bool updateBB)
{
	m_rotation = rotation;
	if (updateBB)
	{
		m_collisionObject->getWorldTransform().setRotation(btQuaternion(rotation.x, rotation.y, rotation.z));
	}
}

void Objects::Entity::SetScale(glm::vec3 scale)
{
	m_scale = scale;
}

std::shared_ptr<Objects::ObjModel> Objects::Entity::GetModel()
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

void Objects::Entity::SetCollisionObject(std::shared_ptr<btCollisionObject> object)
{
	m_collisionObject = object;
}

std::shared_ptr<btCollisionObject> Objects::Entity::GetCollisionObject()
{
	return m_collisionObject;
}