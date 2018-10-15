#include "CollisionDetector.h"

Collision::CollisionDetector::CollisionDetector()
{
	m_collisionConfiguration = std::make_unique<btDefaultCollisionConfiguration>();
	m_collisionDispatcher = std::make_unique<btCollisionDispatcher>(m_collisionConfiguration.get());
	m_collisionBroadphase = std::make_unique<btDbvtBroadphase>();
	m_collisionWorld = std::make_unique<btCollisionWorld>(m_collisionDispatcher.get(), m_collisionBroadphase.get(), m_collisionConfiguration.get());
}
