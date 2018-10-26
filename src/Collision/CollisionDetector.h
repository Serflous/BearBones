#pragma once

#include <memory>
#include <map>
#include <iostream>

#include "../Objects/World.h"
#include "../Physics/PhysicsEngine.h"
#include "../Objects/Entity.h"

namespace Collision
{


	typedef void(*fc)(std::shared_ptr<Objects::Entity> ent1, std::shared_ptr<Objects::Entity> ent2, glm::vec3 direction);

	/**
	 * An Oriented Bounding Box.
	 * @author Mathew Causby
	 * @version 0.1
	 */
	class CollisionDetector
	{
	public:
		CollisionDetector();

		void RegisterEntityForCollision(std::shared_ptr<Objects::Entity> entity);
		void TestForCollisions(fc Callback);

		void SetPhysicsEngine(std::shared_ptr<Physics::PhysicsEngine> engine);
		void SetWorld(std::shared_ptr<Objects::World> world);
	private:
		std::shared_ptr<Physics::PhysicsEngine> m_physicsEngine;
		std::shared_ptr<Objects::World> m_world;

		std::vector <std::shared_ptr<Objects::Entity>> m_registeredEntities;
	};

}
