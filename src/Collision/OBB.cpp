#include "OBB.h"

Collision::OBB::OBB()
{
	m_centerPoint = glm::vec3(0.0f, 0.0f, 0.0f);
	m_minBounds = glm::vec3(0.0f, 0.0f, 0.0f);
	m_maxBounds = glm::vec3(0.0f, 0.0f, 0.0f);
	m_rotation = glm::quat(glm::vec3(0.0f, 0.0f, 0.0f));
}

Collision::OBB::OBB(const OBB & other)
{
	m_centerPoint = other.m_centerPoint;
	m_minBounds = other.m_minBounds;
	m_maxBounds = other.m_maxBounds;
	m_rotation = other.m_rotation;
}

Collision::OBB::OBB(AABB & other)
{
	m_centerPoint.x = (other.GetMaxBounds().x + other.GetMinBounds().x) * 0.5f;
	m_centerPoint.y = (other.GetMaxBounds().y + other.GetMinBounds().y) * 0.5f;
	m_centerPoint.z = (other.GetMaxBounds().z + other.GetMinBounds().z) * 0.5f;

	m_halfSize = HalfSize(other);

	m_axes[0] = glm::vec3(1, 0, 0);
	m_axes[1] = glm::vec3(0, 1, 0);
	m_axes[2] = glm::vec3(0, 0, 1);
}

glm::vec3 Collision::OBB::HalfSize(AABB & other)
{
	return 0.5f * Size();
}

glm::vec3 Collision::OBB::Size() const
{
	return m_maxBounds - m_minBounds;
}

Collision::OBB::~OBB()
{

}

glm::vec3 Collision::OBB::GetAxesX()
{
	return m_axes[0];
}

glm::vec3 Collision::OBB::GetAxesY()
{
	return m_axes[1];
}

glm::vec3 Collision::OBB::GetAxesZ()
{
	return m_axes[1];;
}

glm::vec3 * Collision::OBB::GetAxes()
{
	return m_axes;
}

glm::vec3 Collision::OBB::GetCenterPoint()
{
	return m_centerPoint;
}

glm::vec3 Collision::OBB::GetHalfSize()
{
	return m_halfSize;
}


