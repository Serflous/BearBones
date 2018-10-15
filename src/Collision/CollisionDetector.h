#pragma once

#include <memory>

#include <bullet/btBulletCollisionCommon.h>

namespace Collision
{

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
	private:
		std::unique_ptr<btCollisionConfiguration> m_collisionConfiguration;
		std::unique_ptr<btCollisionWorld> m_collisionWorld;
		std::unique_ptr<btCollisionDispatcher> m_collisionDispatcher;
		std::unique_ptr<btBroadphaseInterface> m_collisionBroadphase;
	};

}
