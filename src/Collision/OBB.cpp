#include "OBB.h"

Collision::OBB::OBB()
{
	m_centerPoint = glm::vec3(0, 0, 0);
	m_rotationMatrix = glm::mat3x3(1.0);
	m_halfWidths = glm::vec3(0, 0, 0);
}

Collision::OBB::OBB(const OBB & other)
{
	m_centerPoint = other.m_centerPoint;
	m_rotationMatrix = other.m_rotationMatrix;
	m_halfWidths = other.m_halfWidths;
}

Collision::OBB::~OBB()
{

}

void Collision::OBB::SetCenterPoint(glm::vec3 point)
{
	m_centerPoint = point;
}

void Collision::OBB::SetRotation(glm::mat3x3 rotation)
{
	m_rotationMatrix = rotation;
}

void Collision::OBB::SetHalfwidth(glm::vec3 halfwidth)
{
	m_halfWidths = halfwidth;
}

glm::vec3 Collision::OBB::GetCenterPoint()
{
	return m_centerPoint;
}

glm::mat3x3 Collision::OBB::GetRotation()
{
	return m_rotationMatrix;
}

glm::vec3 Collision::OBB::GetHalfWidth()
{
	return m_halfWidths;
}

bool Collision::OBB::IsCollidingWith(BoundingVolume & other)
{
	return false;
}

bool Collision::OBB::IsCollidingWith(OBB & other)
{
	float ra, rb;
	glm::mat3x3 R, AbsR;

	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			R[i][j] = glm::dot(m_rotationMatrix[i], other.m_rotationMatrix[j]);
		}
	}

	glm::vec3 t = other.m_centerPoint - m_centerPoint;
	t = glm::vec3(glm::dot(t, m_rotationMatrix[0]), glm::dot(t, m_rotationMatrix[1]), glm::dot(t, m_rotationMatrix[2]));

	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			AbsR[i][j] = glm::abs(R[i][j]) + FLT_EPSILON;
		}
	}

	for (int i = 0; i < 3; i++)
	{
		ra = m_halfWidths[i];
		rb = other.m_halfWidths[0] * AbsR[i][0] + other.m_halfWidths[1] * AbsR[i][1] + other.m_halfWidths[2] * AbsR[i][2];
		if (glm::abs(t[i]) > ra + rb)
		{
			return false;
		}
	}

	for (int i = 0; i < 3; i++)
	{
		ra = m_halfWidths[0] * AbsR[0][i] + m_halfWidths[1] * AbsR[1][i] + m_halfWidths[2] + AbsR[2][i];
		rb = other.m_halfWidths[i];
		if (glm::abs(t[0] * R[0][i] + t[1] * R[1][i] + t[2] * R[2][i]) > ra + rb)
		{
			return false;
		}
	}

	ra = m_halfWidths[1] * AbsR[2][0] + m_halfWidths[2] * AbsR[1][0];
	rb = other.m_halfWidths[1] * AbsR[0][2] + other.m_halfWidths[2] * AbsR[0][1];
	if (glm::abs(t[2] * R[1][0] - t[1] * R[2][0]) > ra + rb)
	{
		return false;
	}

	ra = m_halfWidths[1] * AbsR[2][1] + m_halfWidths[2] * AbsR[1][1];
	rb = other.m_halfWidths[0] * AbsR[0][2] + other.m_halfWidths[2] * AbsR[0][0];
	if (glm::abs(t[2] * R[1][1] - t[1] * R[2][1]) > ra + rb)
	{
		return false;
	}

	ra = m_halfWidths[1] * AbsR[2][2] + m_halfWidths[2] * AbsR[1][2];
	rb = other.m_halfWidths[0] * AbsR[0][1] + other.m_halfWidths[1] * AbsR[0][0];
	if (glm::abs(t[2] * R[1][2] - t[1] * R[2][2]) > ra + rb)
	{
		return false;
	}

	ra = m_halfWidths[0] * AbsR[2][0] + m_halfWidths[2] * AbsR[0][0];
	rb = other.m_halfWidths[1] * AbsR[1][2] + m_halfWidths[2] * AbsR[1][1];
	if (glm::abs(t[0] * R[2][0] - t[2] * R[0][0]) > ra + rb)
	{
		return false;
	}

	ra = m_halfWidths[0] * AbsR[2][1] + m_halfWidths[2] * AbsR[0][1];
	rb = other.m_halfWidths[0] * AbsR[1][2] + other.m_halfWidths[2] * AbsR[1][0];
	if (glm::abs(t[0] * R[2][1] - t[2] * R[0][1]) > ra + rb)
	{
		return false;
	}

	ra = m_halfWidths[0] * AbsR[2][2] + m_halfWidths[2] * AbsR[0][2];
	rb = other.m_halfWidths[0] * AbsR[1][1] + other.m_halfWidths[1] * AbsR[1][0];
	if (glm::abs(t[0] * R[2][2] - t[2] * R[0][2]) > ra + rb)
	{
		return false;
	}

	ra = m_halfWidths[0] * AbsR[1][0] + m_halfWidths[1] * AbsR[0][0];
	rb = other.m_halfWidths[1] * AbsR[2][2] + other.m_halfWidths[2] * AbsR[2][1];
	if (glm::abs(t[1] * R[0][0] - t[0] * R[1][0]) > ra + rb)
	{
		return false;
	}

	ra = m_halfWidths[0] * AbsR[1][1] + m_halfWidths[1] * AbsR[0][1];
	rb = other.m_halfWidths[0] * AbsR[2][2] + other.m_halfWidths[2] * AbsR[2][0];
	if (glm::abs(t[1] * R[0][1] - t[0] * R[1][1]) > ra + rb)
	{
		return false;
	}

	ra = m_halfWidths[0] * AbsR[1][2] + m_halfWidths[1] * AbsR[0][2];
	rb = other.m_halfWidths[0] * AbsR[2][1] + other.m_halfWidths[1] * AbsR[2][0];
	if (glm::abs(t[1] * R[0][2] - t[0] * R[1][2]) > ra + rb)
	{
		return false;
	}

	return true;
}