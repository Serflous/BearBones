#include "StaticEntity.h"

Objects::StaticEntity::StaticEntity() : Entity()
{
	
}

Objects::StaticEntity::StaticEntity(const StaticEntity & other) : Entity(other)
{

}

Objects::StaticEntity::StaticEntity(const Entity & other) : Entity(other)
{

}

Objects::StaticEntity::~StaticEntity()
{

}

void Objects::StaticEntity::CreateBoundingBox()
{
	float minX, minY, minZ, maxX, maxY, maxZ;
	minX = minY = minZ = std::numeric_limits<float>::max();
	maxX = maxY = maxZ = std::numeric_limits<float>::min();
	std::vector<glm::vec3>::iterator iter;
	std::vector<glm::vec3> verts = GetModel()->GetVerticies();
	for (iter = verts.begin(); iter != verts.end(); iter++)
	{
		glm::vec3 vert = (*iter);
		if (vert.x < minX)
			minX = vert.x;
		if (vert.y < minY)
			minY = vert.y;
		if (vert.z < minZ)
			minZ = vert.z;
		if (vert.x > maxX)
			maxX = vert.x;
		if (vert.y > maxY)
			maxY = vert.y;
		if (vert.z > maxZ)
			maxZ = vert.z;
	}
	m_collisionObject = std::make_shared<btCollisionObject>();
	m_collisionObject->setCollisionShape(new btBoxShape(btVector3((maxX - minX) * 0.5f, (maxY - minY) *0.5f, (maxZ - minZ)) * 0.5f));
	glm::vec3 position = GetPosition();
	glm::vec3 rotationEular = GetRotation();
	m_collisionObject->getWorldTransform().setOrigin(btVector3(position.x, position.y, position.z));
	m_collisionObject->getWorldTransform().setRotation(btQuaternion(rotationEular.x, rotationEular.y, rotationEular.z));
}

void Objects::StaticEntity::SetPosition(glm::vec3 position, bool updateBB)
{
	Objects::Entity::SetPosition(position);
	if (updateBB)
	{
		m_collisionObject->getWorldTransform().setOrigin(btVector3(position.x, position.y, position.z));
	}
}

void Objects::StaticEntity::SetRotation(glm::vec3 rotation, bool updateBB)
{
	Objects::Entity::SetRotation(rotation);
	if (updateBB)
	{
		m_collisionObject->getWorldTransform().setRotation(btQuaternion(rotation.x, rotation.y, rotation.z));
	}
}