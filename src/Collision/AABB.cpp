#include "AABB.h"

Collision::AABB::AABB()
{
	m_minBounds = glm::vec3(1.0f);
	m_maxBounds = glm::vec3(1.0f);
}

Collision::AABB::AABB(const AABB & other)
{
	m_minBounds = other.m_maxBounds;
	m_maxBounds = other.m_maxBounds;
}

Collision::AABB::~AABB()
{

}

void Collision::AABB::SetMinBounds(glm::vec3 minBounds)
{
	m_minBounds = minBounds;
}

void Collision::AABB::SetMinBounds(float x, float y, float z)
{
	m_minBounds.x = x;
	m_minBounds.y = y;
	m_minBounds.z = z;
}

void Collision::AABB::SetMaxBounds(glm::vec3 maxBounds)
{
	m_maxBounds = maxBounds;
}

void Collision::AABB::SetMaxBounds(float x, float y, float z)
{
	m_maxBounds.x = x;
	m_maxBounds.y = y;
	m_maxBounds.z = z;
}

glm::vec3 Collision::AABB::GetMinBounds()
{
	return m_minBounds;
}

glm::vec3 Collision::AABB::GetMaxBounds()
{
	return m_maxBounds;
}