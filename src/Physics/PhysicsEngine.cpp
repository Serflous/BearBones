#include "PhysicsEngine.h"



Physics::PhysicsEngine::PhysicsEngine()
{
}


Physics::PhysicsEngine::~PhysicsEngine()
{
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
		(*iter)->Step(delta);
	}
}
