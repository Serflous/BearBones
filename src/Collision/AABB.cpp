#include "AABB.h"

Collision::AABB::AABB()
{
	m_minBounds = glm::vec3(0, 0, 0);
	m_maxBounds = glm::vec3(0, 0, 0);
}

Collision::AABB::AABB(const AABB & other)
{
	m_minBounds = other.m_minBounds;
	m_maxBounds = other.m_maxBounds;
}

Collision::AABB::~AABB()
{

}

void Collision::AABB::SetMinBounds(glm::vec3 minBounds)
{
	m_minBounds = minBounds;
}

void Collision::AABB::SetMaxBounds(glm::vec3 maxBounds)
{
	m_maxBounds = maxBounds;
}

glm::vec3 Collision::AABB::GetMinBounds()
{
	return m_minBounds;
}

glm::vec3 Collision::AABB::GetMaxBounds()
{
	return m_maxBounds;
}

bool Collision::AABB::IsCollidingWith(BoundingVolume & other)
{
	return false;
}

bool Collision::AABB::IsCollidingWith(AABB & other)
{
	if (m_maxBounds.x < other.m_minBounds.x || m_minBounds.x > other.m_maxBounds.x)
	{
		return false;
	}
	if (m_maxBounds.y < other.m_minBounds.y || m_minBounds.y > other.m_maxBounds.y)
	{
		return false;
	}
	if (m_maxBounds.z < other.m_minBounds.z || m_minBounds.z > other.m_maxBounds.z)
	{
		return false;
	}
	return true;
}

bool Collision::AABB::IsCollidingWith(BoundingSphere & other)
{
	double distance = 0;

	for(int i = 0; i < 3; i++)
	{
		if (other.GetPosition()[i] < m_minBounds[i])
		{
			distance += (m_minBounds[i] - other.GetPosition()[i]) * (m_minBounds[i] - other.GetPosition()[i]);
		}
		if (other.GetPosition()[i] > m_maxBounds[i])
		{
			distance += (other.GetPosition()[i] - m_maxBounds[i]) * (other.GetPosition()[i] - m_maxBounds[i]);
		}
	}

	return distance <= pow(other.GetRadius(), 2);
}