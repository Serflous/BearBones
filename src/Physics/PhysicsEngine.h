#pragma once
#include "Objects/RigidBody.h"
#include <vector>
#include <algorithm>
#include <GLM/glm.hpp>
#include <GLM/gtc/constants.hpp>

namespace Physics
{
		/**
		 * Class that contains the physics engine.
		 * @author Mathew Causby
		 * @version 0.1
		 */
	class PhysicsEngine
	{
	public:
		PhysicsEngine();
		~PhysicsEngine();
			/**
			 * Gets the gravity for the physics engine.
			 * @return Vector representing gravity.
			 */
		glm::vec3 GetGravity();
			/**
			 * Sets the gravity for the physics engine.
			 * @param[in] Vector representing gravity.
			 */
		void SetGravity(glm::vec3 gravity);

			/**
			 * Called when an entity collides with the terrain.
			 * @param[in] entity The entity that is colliding with the terrain.
			 * @param[in] penetration The penetration depth of the entity into the terrain.
			 * @param[in] height The height at which the terrain is elevated.
			 * @param[in] dt The delta time, provided in the update.
			 */
		void EntityCollideTerrain(std::shared_ptr<Objects::Entity> entity, float penetration, float height, float dt);
			/**
			 * Handles any entity-based collisions that occur
			 * @param[in] ent1 The former entity that is colliding.
			 * @param[in] ent2 The latter entity that is colliding.
			 * @param[in] cp The coordinates of where the collision took place.
			 * @param[in] penetration The penetration depth of the entity into the other entity.
			 * @param[in] dt The delta time, provided in the update.
			 */
		void EntityCollisionHandler(std::shared_ptr<Objects::Entity> ent1, std::shared_ptr<Objects::Entity> ent2, glm::vec3 cp, float penetration, float dt);

			/**
			 * Registers a rigid body to the physics engine.
			 * @param[in] object Pointer to the rigid body.
			 */
		void RegisterRidigBodyForPhysics(std::shared_ptr<Objects::RigidBody> object);
			/**
			 * Steps through the integrate function of each registered rigid body.
			 * @param[in] delta The delta time, provided in the update.
			 */
		void Simulate(float delta);
	private:
		std::vector<std::shared_ptr<Objects::RigidBody>> m_pObjects;
		glm::vec3 m_gravity;
		const double GROUND_FRICTION = 0.97;
		const double IMPACT_ABSORPTION = 0.8f;
		const double COEFFICIENT_OF_RESTITUTION = 0.5f;
	};

}