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
	btCollisionObject * collisionObject = new btCollisionObject();
	collisionObject->setCollisionShape(new btBoxShape(btVector3(maxX - minX, maxY - minY, maxZ - minZ)));
	glm::vec3 position = GetPosition();
	collisionObject->getWorldTransform().setOrigin(btVector3(position.x, position.y, position.z));
	//m_boundingBox.SetMinBounds(glm::vec3(minX, minY, minZ));
	//m_boundingBox.SetMaxBounds(glm::vec3(maxX, maxY, maxZ));

}