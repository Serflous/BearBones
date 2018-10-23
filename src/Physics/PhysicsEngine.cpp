#include "PhysicsEngine.h"



Physics::PhysicsEngine::PhysicsEngine()
{
	m_gravity = glm::vec3(0, 0, 0);
}


Physics::PhysicsEngine::~PhysicsEngine()
{
}

glm::vec3 Physics::PhysicsEngine::GetGravity()
{
	return m_gravity;
}

void Physics::PhysicsEngine::SetGravity(glm::vec3 gravity)
{
	m_gravity = gravity;
}

void Physics::PhysicsEngine::RegisterRidigBodyForPhysics(std::shared_ptr<Objects::RigidBody> object)
{
	m_pObjects.push_back(object);
}

void Physics::PhysicsEngine::Simulate(float delta)
{
	std::vector<std::shared_ptr<Objects::RigidBody>>::iterator iter;
	for (iter = m_pObjects.begin(); iter != m_pObjects.end(); iter++)
	{
		(*iter)->ApplyGravitationalForce(m_gravity);
		(*iter)->Step(delta);
	}
}
