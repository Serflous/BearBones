#pragma once
#include "Objects/PhysicsEntity.h"
#include <vector>

class PhysicsEngine
{
public:
	PhysicsEngine();
	~PhysicsEngine();

	void AddObject(const Objects::PhysicsEntity& object);
	void Simulate(float delta);
private:
	std::vector< Objects::PhysicsEntity> m_pObjects;
};

