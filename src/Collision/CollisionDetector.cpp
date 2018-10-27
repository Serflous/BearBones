#include "CollisionDetector.h"

Collision::CollisionDetector::CollisionDetector()
{
	
}

void Collision::CollisionDetector::RegisterEntityForCollision(std::shared_ptr<Objects::Entity> entity)
{
	m_registeredEntities.push_back(entity);
}

void Collision::CollisionDetector::TestForCollisions(fc callback)
{
	for (int i = 0; i < m_registeredEntities.size() - 1; i++)
	{
		for (int j = i + 1; j < m_registeredEntities.size(); j++)
		{
			std::shared_ptr<Objects::Entity> ent1 = m_registeredEntities[i];
			std::shared_ptr<Objects::Entity> ent2 = m_registeredEntities[j];
			std::shared_ptr<Collision::BoundingVolume> volume1 = ent1->GetBoundingVolume();
			std::shared_ptr<Collision::BoundingVolume> volume2 = ent2->GetBoundingVolume();
			if (dynamic_cast<Collision::AABB*>(volume1.get()) != nullptr && dynamic_cast<Collision::AABB*>(volume2.get()) != nullptr)
			{
				if (std::dynamic_pointer_cast<Collision::AABB>(volume1)->IsCollidingWith(*(std::dynamic_pointer_cast<Collision::AABB>(volume2))))
				{
					callback(ent1, ent2, glm::vec3(0));
				}
			}
			if (dynamic_cast<Collision::OBB*>(volume1.get()) != nullptr && dynamic_cast<Collision::OBB*>(volume2.get()) != nullptr)
			{
				if (std::dynamic_pointer_cast<Collision::OBB>(volume1)->IsCollidingWith(*(std::dynamic_pointer_cast<Collision::OBB>(volume2))))
				{
					callback(ent1, ent2, glm::vec3(0));
				}
			}
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