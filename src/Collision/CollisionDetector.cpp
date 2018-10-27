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
					glm::vec3 cp1 = ent1->GetPosition();
					glm::vec3 cp2 = ent2->GetPosition();
					glm::vec3 directionToOther = cp2 - cp1;
					glm::vec3 directionToMe = cp1 - cp2;
					glm::vec3 support1 = GetSupport(ent1->GetModel()->GetVerticies(), directionToOther);
					glm::vec3 support2 = GetSupport(ent2->GetModel()->GetVerticies(), directionToMe);
					glm::vec3 supportWorld1 = SupportToWorldSpace(support1, cp1, ent1->GetRotation(), ent1->GetScale());
					glm::vec3 supportWorld2 = SupportToWorldSpace(support2, cp2, ent2->GetRotation(), ent2->GetScale());

					double r1 = sqrt(pow((supportWorld1.x - cp1.x), 2) + pow((supportWorld1.y - cp1.y), 2) + pow((supportWorld1.z - cp1.z), 2));
					double r2 = sqrt(pow((supportWorld2.x - cp2.x), 2) + pow((supportWorld2.y - cp2.y), 2) + pow((supportWorld2.z - cp2.z), 2));
					double totalDistance = sqrt(pow((cp2.x - cp1.x), 2) + pow((cp2.y - cp1.y), 2) + pow((cp2.z - cp1.z), 2));
					if ((r1 + r2) >= totalDistance)
					{
						callback(ent1, ent2, support1);
					}
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

glm::vec3 Collision::CollisionDetector::GetSupport(std::vector <glm::vec3> verts, glm::vec3 d)
{
	float max = std::numeric_limits<float>::min();

	glm::vec3 support = glm::vec3(0, 0, 0);
	for (int i = 0; i < verts.size(); i++)
	{
		glm::vec3 vert = verts[i];
		float dot = glm::dot(vert, d);
		if (dot > max)
		{
			max = dot;
			support = vert;
		}
	}

	return support;
}

glm::vec3 Collision::CollisionDetector::SupportToWorldSpace(glm::vec3 support, glm::vec3 position, glm::vec3 rotation, glm::vec3 scale)
{
	glm::mat4x4 t = glm::translate(glm::mat4x4(1.0f), position);
	glm::mat4x4 r = glm::rotate(glm::mat4x4(1.0f), rotation.x, glm::vec3(1, 0, 0));
	r = glm::rotate(r, rotation.y, glm::vec3(0, 1, 0));
	r = glm::rotate(r, rotation.z, glm::vec3(0, 0, 1));
	glm::mat4x4 s = glm::scale(glm::mat4x4(1.0f), scale);
	return t * r * s * glm::vec4(support.x, support.y, support.z, 1);
}