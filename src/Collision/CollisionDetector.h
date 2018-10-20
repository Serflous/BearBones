#pragma once

#include <memory>
#include <map>
#include <iostream>

#include <bullet/btBulletCollisionCommon.h>

#include "../Objects/Entity.h"

namespace Collision
{


	typedef void(*fc)(std::shared_ptr<Objects::Entity> ent1, std::shared_ptr<Objects::Entity> ent2);

	/**
	 * An Oriented Bounding Box.
	 * @author Mathew Causby
	 * @version 0.1
	 * @todo Make Sure in TestOBBOBB that t = glm::vec3(glm::dot(t, aAxis[0]), glm::dot(t, aAxis[2]), glm::dot(t, aAxis[2])) is meant to be x, z, z axes
	 */
	class CollisionDetector
	{
	public:
		CollisionDetector();

		void RegisterEntityForCollision(std::shared_ptr<Objects::Entity> entity);
		void TestForCollisions(fc Callback);
	private:
		std::unique_ptr<btCollisionConfiguration> m_collisionConfiguration;
		std::unique_ptr<btCollisionWorld> m_collisionWorld;
		std::unique_ptr<btCollisionDispatcher> m_collisionDispatcher;
		std::unique_ptr<btBroadphaseInterface> m_collisionBroadphase;
		
		std::map<const btCollisionObject*, std::shared_ptr<Objects::Entity>> m_collisionObjectLookup;

		const int WORLD_SIZE = 1000;
	};

}
