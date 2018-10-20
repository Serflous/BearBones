#include "RigidBody.h"


Objects::RigidBody::RigidBody(float mass, glm::vec3 position, float length, float width, float height)
{
	m_mass = mass;
	m_volume = 0;
	m_lift = 0;
	m_speed = 0;

	lwh[0] = length;
	lwh[1] = width;
	lwh[2] = height;

	m_position = position;

	m_force = glm::vec3(0, 0, 0);
	m_velocity = glm::vec3(0, 0, 0);
	m_acceleration = glm::vec3(0, 0, 0);
}

Objects::RigidBody::RigidBody() : Entity()
{
	m_mass = 1;
	m_volume = 0;
	m_lift = 0;
	m_speed = 0;

	m_position = glm::vec3(0, 0, 0);
	m_force = glm::vec3(0, 0, 0);
	m_velocity = glm::vec3(0, 0, 0);
	m_acceleration = glm::vec3(0, 0, 0);

}

Objects::RigidBody::RigidBody(const RigidBody & other) : Entity(other)
{

}

Objects::RigidBody::RigidBody(const Entity & other) : Entity(other)
{

}

float Objects::RigidBody::getMass()
{
	return m_mass;
}

float * Objects::RigidBody::getLengthWidthHeight()
{
	return nullptr;
}

float Objects::RigidBody::getSpeed()
{
	return m_speed;
}

float Objects::RigidBody::getVolume()
{
	return m_volume;
}

float Objects::RigidBody::getLift()
{
	return m_lift;
}

glm::vec3 Objects::RigidBody::getVelocity()
{
	return m_velocity;
}


void Objects::RigidBody::CreateBoundingBox()
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
	m_collisionObject->setCollisionShape(new btBoxShape(btVector3((maxX - minX) * 0.5f, (maxY - minY) * 0.5f, (maxZ - minZ)) * 0.5f));
	glm::vec3 position = GetPosition();
	glm::vec3 rotationEular = GetRotation();
	m_collisionObject->getWorldTransform().setOrigin(btVector3(position.x, position.y, position.z));
	m_collisionObject->getWorldTransform().setRotation(btQuaternion(rotationEular.x, rotationEular.y, rotationEular.z));
	//m_boundingBox.SetMinBounds(glm::vec3(minX, minY, minZ));
	//m_boundingBox.SetMaxBounds(glm::vec3(maxX, maxY, maxZ));

}

Objects::RigidBody::~RigidBody()
{

}