#include "RigidBody.h"


Objects::RigidBody::RigidBody(float mass, glm::vec3 position, float length, float width, float height)
{
	/*m_mass = mass;
	m_volume = 0;
	m_lift = 0;
	m_speed = 0;

	lwh[0] = length;
	lwh[1] = width;
	lwh[2] = height;

	m_position = position;

	m_force = glm::vec3(0, 0, 0);*/
	m_velocity = glm::vec3(0, 0, 0);
	/*m_acceleration = glm::vec3(0, 0, 0);*/
}

Objects::RigidBody::RigidBody() : Entity()
{/*
	
	m_volume = 0;
	m_lift = 0;
	m_speed = 0;

	m_position = glm::vec3(0, 0, 0);
	m_force = glm::vec3(0, 0, 0);*/
	m_mass = 1;

	m_velocity = glm::vec3(0, 0, 0);
	m_acceleration = glm::vec3(0, 0, 0);
	m_torque = glm::vec3(0, 0, 0);
	m_force = glm::vec3(0, 0, 0);

}
void Objects::RigidBody::SetVelocity(glm::vec3 velocity)
{
	m_velocity = velocity;
}

void Objects::RigidBody::SetAcceleration(glm::vec3 acceleration)
{
	m_acceleration = acceleration;
}

void Objects::RigidBody::SetRotationalVelocity(glm::vec3 rotationalVelocity)
{
	m_rotationalVelocity = rotationalVelocity;
}

void Objects::RigidBody::SetTorque(glm::vec3 torque)
{
	m_torque = torque;
}

void Objects::RigidBody::SetMass(float mass)
{
	m_mass = mass;
}

void Objects::RigidBody::SetGrounded(bool grounded)
{
	m_grounded = grounded;
}

bool Objects::RigidBody::HasVelocity()
{
	return (m_velocity.x > 0 || m_velocity.y > 0 || m_velocity.z > 0);
}

Objects::RigidBody::RigidBody(const RigidBody & other) : Entity(other)
{

}

Objects::RigidBody::RigidBody(const Entity & other) : Entity(other)
{

}

//float Objects::RigidBody::getMass()
//{
//	return m_mass;
//}
//
//float * Objects::RigidBody::getLengthWidthHeight()
//{
//	return nullptr;
//}
//
//float Objects::RigidBody::getSpeed()
//{
//	return m_speed;
//}
//
//float Objects::RigidBody::getVolume()
//{
//	return m_volume;
//}
//
//float Objects::RigidBody::getLift()
//{
//	return m_lift;
//}

glm::vec3 Objects::RigidBody::getVelocity()
{
	return m_velocity;
}

glm::vec3 Objects::RigidBody::GetAcceleration()
{
	return m_acceleration;
}

glm::vec3 Objects::RigidBody::GetRotationalVelocity()
{
	return m_rotationalVelocity;
}

glm::vec3 Objects::RigidBody::GetTorque()
{
	return m_torque;
}

float Objects::RigidBody::GetMass()
{
	return m_mass;
}

bool Objects::RigidBody::GetGrounded()
{
	return m_grounded;
}

void Objects::RigidBody::ApplyGravitationalForce(glm::vec3 gravity)
{
	if (!m_grounded)
	{
		m_velocity += gravity;
	}
}

void Objects::RigidBody::ApplyFriction(double friction)
{
	if (m_grounded)
	{

		m_velocity *= friction;
	}
}

void Objects::RigidBody::ApplyForceFromRigidBody(std::shared_ptr<Objects::RigidBody> other, glm::vec3 direction)
{
	glm::vec3 relativeAcceleration = m_velocity + other->getVelocity();

	m_velocity = (relativeAcceleration * 0.5f) * direction;
	//m_velocity += force;
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
	m_width = maxX - minX;
	m_height = maxY - minY;
	m_depth = maxZ - minZ;
	CalculateInertiaTensor(); // putting this here for simplicity sake
	glm::vec3 position = GetPosition();
	glm::vec3 rotationEular = GetRotation();
	m_collisionObject->getWorldTransform().setOrigin(btVector3(position.x, position.y, position.z));
	m_collisionObject->getWorldTransform().setRotation(btQuaternion(rotationEular.x, rotationEular.y, rotationEular.z));
	//m_boundingBox.SetMinBounds(glm::vec3(minX, minY, minZ));
	//m_boundingBox.SetMaxBounds(glm::vec3(maxX, maxY, maxZ));

}

void Objects::RigidBody::Step(float dt)
{
	glm::vec3 position = GetPosition();
	glm::vec3 rotation = GetRotation();
	m_force = m_mass * m_acceleration;
	m_velocity += m_acceleration * dt;
	m_rotationalVelocity += m_torque * dt;
	position += m_velocity * dt;
	rotation += m_rotationalVelocity * dt;
	SetRotation(rotation, true);
	SetPosition(position, true);

}

Objects::RigidBody::~RigidBody()
{

}

void Objects::RigidBody::CalculateInertiaTensor()
{
	float ih = 0.8333 * m_mass * ((m_width * m_width) + (m_depth * m_depth));
	float iw = 0.8333 * m_mass * ((m_depth * m_depth) + (m_height * m_height));
	float id = 0.8333 * m_mass * ((m_width * m_width) + (m_height * m_height));
	//https://www.toptal.com/game/video-game-physics-part-i-an-introduction-to-rigid-body-dynamics
	float i = (m_mass * (m_width * m_width + m_depth * m_depth + m_height * m_height)) / 12;

}
