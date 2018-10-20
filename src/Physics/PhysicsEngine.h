#pragma once
#include "Objects/RigidBody.h"
#include <vector>

class PhysicsEngine
{
public:
	PhysicsEngine();
	~PhysicsEngine();

	void AddObject(const Objects::RigidBody& object);
	void Simulate(float delta);
private:
	std::vector< Objects::RigidBody> m_pObjects;
};

