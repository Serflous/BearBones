#pragma once
#include "Objects/RigidBody.h"
#include <vector>
#include <algorithm>
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

		void EntityCollideTerrain(std::shared_ptr<Objects::Entity> entity, float penetration, float height, float dt);
		void EntityCollisionHandler(std::shared_ptr<Objects::Entity> ent1, std::shared_ptr<Objects::Entity> ent2, glm::vec3 cp, float penetration, float dt);

		void RegisterRidigBodyForPhysics(std::shared_ptr<Objects::RigidBody> object);
		void Simulate(float delta);
	private:
		std::vector<std::shared_ptr<Objects::RigidBody>> m_pObjects;
		glm::vec3 m_gravity;
		const double GROUND_FRICTION = 0.97;
		const double IMPACT_ABSORPTION = 0.8f;
		const double COEFFICIENT_OF_RESTITUTION = 0.5f;
	};

}