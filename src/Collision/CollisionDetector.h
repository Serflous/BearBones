#pragma once

#include <memory>
#include <map>
#include <iostream>

#include <bullet/btBulletCollisionCommon.h>

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

		void Update(float dt);

		void SetPhysicsEngine(std::shared_ptr<Physics::PhysicsEngine> engine);
		void SetWorld(std::shared_ptr<Objects::World> world);
	private:
		std::unique_ptr<btCollisionConfiguration> m_collisionConfiguration;
		std::unique_ptr<btCollisionWorld> m_collisionWorld;
		std::unique_ptr<btCollisionDispatcher> m_collisionDispatcher;
		std::unique_ptr<btBroadphaseInterface> m_collisionBroadphase;
		
		std::map<const btCollisionObject*, std::shared_ptr<Objects::Entity>> m_collisionObjectLookup;
		std::shared_ptr<Physics::PhysicsEngine> m_physicsEngine;
		std::shared_ptr<Objects::World> m_world;

		const int WORLD_SIZE = 1000;
	};

}
