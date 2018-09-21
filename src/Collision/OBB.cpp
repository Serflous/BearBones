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

Collision::OBB::~OBB()
{

}