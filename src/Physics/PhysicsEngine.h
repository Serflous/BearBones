#pragma once
#include "Objects/RigidBody.h"
#include <vector>

namespace Physics
{

	class PhysicsEngine
	{
	public:
		PhysicsEngine();
		~PhysicsEngine();
		float GetGravity();
		void SetGravity(float gravity);

		void RegisterRidigBodyForPhysics(std::shared_ptr<Objects::RigidBody> object);
		void Simulate(float delta);
	private:
		std::vector<std::shared_ptr<Objects::RigidBody>> m_pObjects;
		float m_gravity;
	};

}