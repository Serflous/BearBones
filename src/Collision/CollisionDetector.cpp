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

void Collision::CollisionDetector::TestForCollisions(fc callback)
{
	m_collisionWorld->performDiscreteCollisionDetection();
	int nMan = m_collisionWorld->getDispatcher()->getNumManifolds();
	for (int i = 0; i < nMan; i++)
	{
		// Get collisions Objects
		btPersistentManifold * manifold = m_collisionWorld->getDispatcher()->getManifoldByIndexInternal(i);
		std::shared_ptr<btCollisionObject> object1 = std::make_shared<btCollisionObject>(*(manifold->getBody0()));
		std::shared_ptr<btCollisionObject> object2 = std::make_shared<btCollisionObject>(*(manifold->getBody1()));
		std::shared_ptr<Objects::Entity> entity1 = m_collisionObjectLookup[object1];
		std::shared_ptr<Objects::Entity> entity2 = m_collisionObjectLookup[object2];
		// Get contact points
		// Alert callback

		callback(entity1, entity2);
	}
}