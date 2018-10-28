#include "PhysicsEngine.h"



Physics::PhysicsEngine::PhysicsEngine()
{
	m_gravity = glm::vec3(0, 0, 0);
}


Physics::PhysicsEngine::~PhysicsEngine()
{
}

glm::vec3 Physics::PhysicsEngine::GetGravity()
{
	return m_gravity;
}

void Physics::PhysicsEngine::EntityCollideTerrain(std::shared_ptr<Objects::Entity> entity, float penetration, float height, float dt)
{
	std::vector<std::shared_ptr<Objects::RigidBody>>::iterator iter = std::find(m_pObjects.begin(), m_pObjects.end(), entity);
	if (iter != m_pObjects.end())
	{
		glm::vec3 pos = (*iter)->GetPosition();
		glm::vec3 velocity = (*iter)->GetVelocity();
		pos.y = pos.y + abs(penetration);
		velocity.y *= -1 / ((*iter)->GetMass() + 1);
		velocity *= GROUND_FRICTION;
		(*iter)->SetPosition(pos);
		(*iter)->SetVelocity(velocity);
		
	}
}

void Physics::PhysicsEngine::EntityCollisionHandler(std::shared_ptr<Objects::Entity> ent1, std::shared_ptr<Objects::Entity> ent2, glm::vec3 cp, float penetration, float dt)
{
	std::vector<std::shared_ptr<Objects::RigidBody>>::iterator iter1, iter2;
	iter1 = std::find(m_pObjects.begin(), m_pObjects.end(), ent1);
	iter2 = std::find(m_pObjects.begin(), m_pObjects.end(), ent2);
	if (iter1 != m_pObjects.end() && iter2 != m_pObjects.end())
	{
		glm::vec3 directionToContact = (*iter1)->GetCenterOfGravity() - cp;
		glm::vec3 velocity1 = (*iter1)->GetVelocity();
		glm::vec3 velocity2 = (*iter2)->GetVelocity();
		glm::vec3 position1 = (*iter1)->GetPosition();
		glm::vec3 position2 = (*iter2)->GetPosition();
		glm::vec3 relativeVelocity = (*iter1)->GetVelocity() - (*iter2)->GetVelocity();
		float contactVelocity = glm::dot(relativeVelocity, glm::normalize(directionToContact));
		if (contactVelocity > 0)
		{
			return;
		}
		float impulseValue = -(1.0f + COEFFICIENT_OF_RESTITUTION) * contactVelocity;
		impulseValue /= (1 / (*iter1)->GetMass()) + (1 / (*iter2)->GetMass());
		glm::vec3 impulse = impulseValue * directionToContact;
		velocity1 += impulse * (float)(1 / (*iter1)->GetMass());
		velocity2 -= impulse * (float)(1 / (*iter2)->GetMass());
		(*iter1)->SetVelocity(velocity1);
		(*iter2)->SetVelocity(velocity2);
	}
}

void Physics::PhysicsEngine::SetGravity(glm::vec3 gravity)
{
	m_gravity = gravity;
}

void Physics::PhysicsEngine::RegisterRidigBodyForPhysics(std::shared_ptr<Objects::RigidBody> object)
{
	m_pObjects.push_back(object);
}

void Physics::PhysicsEngine::Simulate(float delta)
{
	std::vector<std::shared_ptr<Objects::RigidBody>>::iterator iter;
	for (iter = m_pObjects.begin(); iter != m_pObjects.end(); iter++)
	{
		(*iter)->ApplyGravity(m_gravity, delta);
		(*iter)->Integrate(delta);
	}
}
