#include "PhysicsEngine.h"



Physics::PhysicsEngine::PhysicsEngine()
{
	m_gravity = 0.0f;
}


Physics::PhysicsEngine::~PhysicsEngine()
{
}

float Physics::PhysicsEngine::GetGravity()
{
	return m_gravity;
}

void Physics::PhysicsEngine::SetGravity(float gravity)
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
		(*iter)->SetGravity(m_gravity);
		(*iter)->Step(delta);
	}
}
