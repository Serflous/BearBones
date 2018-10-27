#include "RigidBody.h"

Objects::RigidBody::RigidBody()
{
	m_mass = 0;
	m_velocity = glm::vec3(0, 0, 0);
}

Objects::RigidBody::RigidBody(const RigidBody & other)
{
	m_mass = other.m_mass;
	m_velocity = other.m_velocity;
}

Objects::RigidBody::~RigidBody()
{

}

void Objects::RigidBody::CreateBoundingBox(Util::BB_BoundingVolume type)
{
	m_volumeType = type;
	if (type == Util::BB_BV_AABB)
	{
		UpdateBoundingBox();
	}
	else if (type == Util::BB_BV_OBB)
	{
		float minX, minY, minZ, maxX, maxY, maxZ;
		minX = minY = minZ = std::numeric_limits<float>::max();
		maxX = maxY = maxZ = std::numeric_limits<float>::min();
		std::vector<glm::vec3>::iterator iter;
		std::vector<glm::vec3> verts = GetModel()->GetVerticies();
		glm::vec3 position = GetPosition();
		glm::mat4x4 t = glm::translate(glm::mat4x4(1.0f), position);
		glm::mat4x4 r = glm::rotate(glm::mat4x4(1.0f), GetRotation().x, glm::vec3(1, 0, 0));
		r = glm::rotate(r, GetRotation().y, glm::vec3(0, 1, 0));
		r = glm::rotate(r, GetRotation().z, glm::vec3(0, 0, 1));
		glm::mat4x4 s = glm::scale(glm::mat4x4(1.0f), GetScale());

		for (iter = verts.begin(); iter != verts.end(); iter++)
		{
			glm::vec3 initVert = (*iter);
			glm::vec4 vert = glm::vec4(initVert.x, initVert.y, initVert.z, 1.0f);
			vert = s * vert;
			if (vert.x < minX)
				minX = vert.x;
			if (vert.y < minY)
				minY = vert.y;
			if (vert.z < minZ)
				minZ = vert.z;
			if (vert.x > maxX)
				maxX = vert.x;
			if (vert.y > maxY)
				maxY = vert.y;
			if (vert.z > maxZ)
				maxZ = vert.z;
		}
		glm::vec3 centerPoint = glm::vec3
		(
			(minX + maxX) / 2.0,
			(minY + maxY) / 2.0,
			(minZ + maxZ) / 2.0
		);
		centerPoint.x += t[3][0];
		centerPoint.y += t[3][1];
		centerPoint.z += t[3][2];
		glm::mat4x4 rotationMatrix = r;
		glm::vec3 halfWidths = glm::vec3
		(
			(glm::abs(minX) + glm::abs(maxX)) / 2.0,
			(glm::abs(minY) + glm::abs(maxY)) / 2.0,
			(glm::abs(minZ) + glm::abs(maxZ)) / 2.0
		);
		m_boundingVolume = std::make_shared<Collision::OBB>();
		std::dynamic_pointer_cast<Collision::OBB>(m_boundingVolume)->SetCenterPoint(centerPoint);
		std::dynamic_pointer_cast<Collision::OBB>(m_boundingVolume)->SetRotation(rotationMatrix);
		std::dynamic_pointer_cast<Collision::OBB>(m_boundingVolume)->SetHalfwidth(halfWidths);
	}
}

void Objects::RigidBody::UpdateBoundingBox()
{
	if (m_volumeType == Util::BB_BV_AABB)
	{
		float minX, minY, minZ, maxX, maxY, maxZ;
		minX = minY = minZ = std::numeric_limits<float>::max();
		maxX = maxY = maxZ = std::numeric_limits<float>::min();
		std::vector<glm::vec3>::iterator iter;
		std::vector<glm::vec3> verts = GetModel()->GetVerticies();
		glm::mat4x4 t = glm::translate(glm::mat4x4(1.0f), GetPosition());
		glm::mat4x4 r = glm::rotate(glm::mat4x4(1.0f), GetRotation().x, glm::vec3(1, 0, 0));
		r = glm::rotate(r, GetRotation().y, glm::vec3(0, 1, 0));
		r = glm::rotate(r, GetRotation().z, glm::vec3(0, 0, 1));
		glm::mat4x4 s = glm::scale(glm::mat4x4(1.0f), GetScale());

		for (iter = verts.begin(); iter != verts.end(); iter++)
		{
			glm::vec3 initVert = (*iter);
			glm::vec4 vert = glm::vec4(initVert.x, initVert.y, initVert.z, 1.0f);
			vert = t * r * s * vert;
			if (vert.x < minX)
				minX = vert.x;
			if (vert.y < minY)
				minY = vert.y;
			if (vert.z < minZ)
				minZ = vert.z;
			if (vert.x > maxX)
				maxX = vert.x;
			if (vert.y > maxY)
				maxY = vert.y;
			if (vert.z > maxZ)
				maxZ = vert.z;
		}

		m_boundingVolume = std::make_shared<Collision::AABB>();
		std::dynamic_pointer_cast<Collision::AABB>(m_boundingVolume)->SetMinBounds(glm::vec3(minX, minY, minZ));
		std::dynamic_pointer_cast<Collision::AABB>(m_boundingVolume)->SetMaxBounds(glm::vec3(maxX, maxY, maxZ));
	}
	else if (m_volumeType == Util::BB_BV_OBB)
	{
		glm::vec3 centerPoint = GetPosition();
		std::dynamic_pointer_cast<Collision::OBB>(m_boundingVolume)->SetCenterPoint(centerPoint);
	}
}

void Objects::RigidBody::SetMass(double mass)
{
	m_mass = mass;
}

void Objects::RigidBody::SetVelocity(glm::vec3 velocity)
{
	m_velocity = velocity;
}

double Objects::RigidBody::GetMass()
{
	return m_mass;
}

glm::vec3 Objects::RigidBody::GetVelocity()
{
	return m_velocity;
}

void Objects::RigidBody::Integrate(double dt)
{
	glm::vec3 position = GetPosition();

	position += m_velocity * (float)(dt / 1000.0f);

	SetPosition(position);
	UpdateBoundingBox();
}

void Objects::RigidBody::ApplyGravity(glm::vec3 gravity, double dt)
{
	m_velocity += gravity * (float)(dt / 1000.0f);
}

void Objects::RigidBody::ApplyForce(glm::vec3 force, double dt)
{
	m_velocity += (force / (float)m_mass) * (float)(dt / 1000.0f);
}