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
			if (contactNo >= 3)
			{
				btVector3 v = manifold->getContactPoint(0).getPositionWorldOnA();
				glm::vec3 A = glm::vec3((float)v.getX(), (float)v.getY(), (float)v.getZ());
				v = manifold->getContactPoint(1).getPositionWorldOnA();
				glm::vec3 B = glm::vec3((float)v.getX(), (float)v.getY(), (float)v.getZ());
				v = manifold->getContactPoint(2).getPositionWorldOnA();
				glm::vec3 C = glm::vec3((float)v.getX(), (float)v.getY(), (float)v.getZ());

				glm::vec3 N = glm::cross(A - B, B - C);
				if (glm::length(N) > 0)
				{
					N = glm::normalize(N);
				}
				
				// Rigid body to Rigid Body
				if (dynamic_cast<Objects::RigidBody*>(entity1.get()) != nullptr && dynamic_cast<Objects::RigidBody*>(entity2.get()) != nullptr)
				{
					std::dynamic_pointer_cast<Objects::RigidBody>(entity1)->ApplyForceFromRigidBody(std::dynamic_pointer_cast<Objects::RigidBody>(entity2), N);
					std::dynamic_pointer_cast<Objects::RigidBody>(entity2)->ApplyForceFromRigidBody(std::dynamic_pointer_cast<Objects::RigidBody>(entity1), N);
					std::dynamic_pointer_cast<Objects::RigidBody>(entity1)->SetGrounded(false);
					std::dynamic_pointer_cast<Objects::RigidBody>(entity2)->SetGrounded(false);
				}
				callback(entity1, entity2, N);
			}
		}
	}
}

void Collision::CollisionDetector::Update(float dt)
{
	std::shared_ptr<std::vector<std::shared_ptr<Objects::RigidBody>>> rbs = m_world->GetRigidBodies();
	std::vector<std::shared_ptr<Objects::RigidBody>>::iterator rbIter;
	for (rbIter = rbs->begin(); rbIter != rbs->end(); rbIter++)
	{
		if ((*rbIter)->GetPosition().y <= 0)
		{
			(*rbIter)->SetGrounded(true);
			if ((*rbIter)->getVelocity().y < 0)
			{
				glm::vec3 velocity = (*rbIter)->getVelocity();

				velocity.y *= -0.4f;
				(*rbIter)->SetVelocity(velocity);
			}
		}
		else
		{
			(*rbIter)->SetGrounded(false);
		}
	}
}

void Collision::CollisionDetector::SetPhysicsEngine(std::shared_ptr<Physics::PhysicsEngine> engine)
{
	m_physicsEngine = engine;
}

void Collision::CollisionDetector::SetWorld(std::shared_ptr<Objects::World> world)
{
	m_world = world;
}