#include "CollisionDetector.h"

Collision::CollisionDetector::CollisionDetector()
{
	btVector3 boxMin(-WORLD_SIZE, -WORLD_SIZE, -WORLD_SIZE);
	btVector3 boxMax(WORLD_SIZE, WORLD_SIZE, WORLD_SIZE);

	m_collisionConfiguration = std::make_unique<btDefaultCollisionConfiguration>();
	m_collisionDispatcher = std::make_unique<btCollisionDispatcher>(m_collisionConfiguration.get());
	m_collisionBroadphase = std::make_unique<bt32BitAxisSweep3>(boxMin, boxMax, 1000, nullptr, true);
	m_collisionWorld = std::make_unique<btCollisionWorld>(m_collisionDispatcher.get(), m_collisionBroadphase.get(), m_collisionConfiguration.get());
	m_collisionWorld->setForceUpdateAllAabbs(true);
}

void Collision::CollisionDetector::RegisterEntityForCollision(std::shared_ptr<Objects::Entity> entity)
{
	m_collisionWorld->addCollisionObject(entity->GetCollisionObject().get());
	m_collisionObjectLookup[entity->GetCollisionObject().get()] = entity;
}

void Collision::CollisionDetector::TestForCollisions(fc callback)
{
	m_collisionWorld->performDiscreteCollisionDetection();
	int nMan = m_collisionWorld->getDispatcher()->getNumManifolds();
	for (int i = 0; i < nMan; i++)
	{
		// Get collisions Objects
		btPersistentManifold * manifold = m_collisionWorld->getDispatcher()->getManifoldByIndexInternal(i);
		std::shared_ptr<Objects::Entity> entity1 = m_collisionObjectLookup[manifold->getBody0()];
		std::shared_ptr<Objects::Entity> entity2 = m_collisionObjectLookup[manifold->getBody1()];
		// Get contact points
		manifold->refreshContactPoints(manifold->getBody0()->getWorldTransform(), manifold->getBody1()->getWorldTransform());
		int contactNo = manifold->getNumContacts();
		if (contactNo > 0)
		{
			//std::cout << "Contact no: " << contactNo << std::endl;
			for (int j = 0; j < contactNo; j++)
			{
				//std::cout << "Vector " << j + 1 << " A: " << manifold->getContactPoint(j).getPositionWorldOnA().getX() << "," << manifold->getContactPoint(j).getPositionWorldOnA().getY() << "," << manifold->getContactPoint(j).getPositionWorldOnA().getZ() << std::endl;
				//std::cout << "Vector " << j + 1 << " B: " << manifold->getContactPoint(j).getPositionWorldOnB().getX() << "," << manifold->getContactPoint(j).getPositionWorldOnB().getY() << "," << manifold->getContactPoint(j).getPositionWorldOnB().getZ() << std::endl;
			}
			// Alert callback

			callback(entity1, entity2);
		}
	}
}