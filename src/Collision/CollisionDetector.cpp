#include "CollisionDetector.h"

Collision::CollisionDetector::CollisionDetector()
{
	m_collisionConfiguration = std::make_unique<btDefaultCollisionConfiguration>();
	m_collisionDispatcher = std::make_unique<btCollisionDispatcher>(m_collisionConfiguration.get());
	m_collisionBroadphase = std::make_unique<btDbvtBroadphase>();
	m_collisionWorld = std::make_unique<btCollisionWorld>(m_collisionDispatcher.get(), m_collisionBroadphase.get(), m_collisionConfiguration.get());
}

void Collision::CollisionDetector::RegisterEntityForCollision(std::shared_ptr<Objects::Entity> entity)
{
	m_collisionWorld->addCollisionObject(entity->GetCollisionObject().get());
	m_collisionObjectLookup[entity->GetCollisionObject()] = entity;
}

void Collision::CollisionDetector::TestForCollisions()
{
	m_collisionWorld->performDiscreteCollisionDetection();
	int nMan = m_collisionWorld->getDispatcher()->getNumManifolds();
	for (int i = 0; i < nMan; i++)
	{
		// Get collisions Objects
		// Get contact points
		// Alert callback
	}
}