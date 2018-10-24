#pragma once
#include "Objects/RigidBody.h"
#include <vector>
#include <GLM/glm.hpp>
#include <GLM/gtc/constants.hpp>

namespace Physics
{

	class PhysicsEngine
	{
	public:
		PhysicsEngine();
		~PhysicsEngine();
		glm::vec3 GetGravity();
		void SetGravity(glm::vec3 gravity);

		void RegisterRidigBodyForPhysics(std::shared_ptr<Objects::RigidBody> object);
		void Simulate(float delta);
	private:
		std::vector<std::shared_ptr<Objects::RigidBody>> m_pObjects;
		glm::vec3 m_gravity;
		const double GROUND_FRICTION = 0.95;
	};

}