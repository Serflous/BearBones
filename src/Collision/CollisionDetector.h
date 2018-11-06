#pragma once

#include <memory>
#include <map>
#include <iostream>

#include <GLM/gtc/matrix_transform.hpp>

#include "../Objects/World.h"
#include "../Physics/PhysicsEngine.h"
#include "../Objects/Entity.h"

namespace Collision
{


	typedef void(*fc)(std::shared_ptr<Objects::Entity> ent1, std::shared_ptr<Objects::Entity> ent2, glm::vec3 direction);

		/**
		 * Handler for detecting collisions.
		 * @author Mathew Causby
		 * @version 0.1
		 */
	class CollisionDetector
	{
	public:
		CollisionDetector();

			/**
			 * Registers an entity to be checked for collisions.
			 * @param[in] The entity to apply physics to.
			 */
		void RegisterEntityForCollision(std::shared_ptr<Objects::Entity> entity);

			/**
			 * Tests to see if any collisions are occurring.
			 * @param[in] Callback
			 * @param[in] dt The delta time, provided in the update.
			 */
		void TestForCollisions(fc Callback, float dt);

			/**
			 * Sets the physics engine for use.
			 * @param[in] engine The physics engine.
			 */
		void SetPhysicsEngine(std::shared_ptr<Physics::PhysicsEngine> engine);

			/**
			 * Sets the game world for use.
			 * @param[in] world The game world.
			 */
		void SetWorld(std::shared_ptr<Objects::World> world);

	private:
			/**
			 * Gets the support vector along a vector. The support point is the furthest vertex along a vector.
			 * @param[in] The verticies to find the support
			 * @param[in] The direction of the vector
			 */
		glm::vec3 GetSupport(std::vector <glm::vec3> verts, glm::vec3 d);

			/**
			 * Brings the support point into world space.
			 * @param[in] support The support.
			 * @param[in] position The position to set the support to.
			 * @param[in] rotation The rotation to apply to the support.
			 * @param[in] scale The scaling to apply to the support.
			 * @return The support point in world space.
			 */
		glm::vec3 SupportToWorldSpace(glm::vec3 support, glm::vec3 position, glm::vec3 rotation, glm::vec3 scale);

			/**
			 * Tests an entity against the terrain.
			 * @param[in] entity The entity.
			 * @param[in] dt The delta time, provided in the update.
			 */
		void TestEntityAgainstTerrain(std::shared_ptr<Objects::Entity> entity, float dt);
	private:
		std::shared_ptr<Physics::PhysicsEngine> m_physicsEngine;
		std::shared_ptr<Objects::World> m_world;

		std::vector <std::shared_ptr<Objects::Entity>> m_registeredEntities;
	};

}
