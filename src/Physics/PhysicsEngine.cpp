#include "PhysicsEngine.h"



PhysicsEngine::PhysicsEngine()
{
}


PhysicsEngine::~PhysicsEngine()
{
}

void PhysicsEngine::AddObject(const Objects::RigidBody& object)
{
	m_pObjects.push_back(object);
}

void PhysicsEngine::Simulate(float delta)
{
	for (unsigned int i = 0; i < m_pObjects.size(); i++) {
	}
}
