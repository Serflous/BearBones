#include "BoundingSphere.h"

Collision::BoundingSphere::BoundingSphere()
{
	m_position = glm::vec3(0, 0, 0);
	m_radius = 0;
}

Collision::BoundingSphere::BoundingSphere(const BoundingSphere & other)
{
	m_position = other.m_position;
	m_radius = other.m_radius;
}

Collision::BoundingSphere::~BoundingSphere()
{

}

void Collision::BoundingSphere::SetPosition(glm::vec3 position)
{
	m_position = position;
}

void Collision::BoundingSphere::SetRadius(double radius)
{
	m_radius = radius;
}

glm::vec3 Collision::BoundingSphere::GetPosition()
{
	return m_position;
}

double Collision::BoundingSphere::GetRadius()
{
	return m_radius;
}

bool Collision::BoundingSphere::IsCollidingWith(BoundingVolume & other)
{
	return false;
}

bool Collision::BoundingSphere::IsCollidingWith(BoundingSphere & sphere)
{
	double combinedRadious = m_radius + sphere.m_radius;
	double distance = sqrt(
		(pow(sphere.m_position.x - m_position.x, 2)) +
		(pow(sphere.m_position.y - m_position.y, 2)) +
		(pow(sphere.m_position.z - m_position.z, 2))
	);
	return distance <= combinedRadious;
}

bool Collision::BoundingSphere::IsCollidingWith(AABB & box)
{
	double distance = 0;

	for (int i = 0; i < 3; i++)
	{
		if (m_position[i] < box.GetMinBounds()[i])
		{
			distance += (box.GetMinBounds()[i] - m_position[i]) * (box.GetMinBounds()[i] - m_position[i]);
		}
		if (m_position[i] > box.GetMaxBounds()[i])
		{
			distance += (m_position[i] - box.GetMaxBounds()[i]) * (m_position[i] - box.GetMaxBounds()[i]);
		}
	}

	return distance <= pow(m_radius, 2);
}