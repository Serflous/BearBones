#include "StaticEntity.h"

Objects::StaticEntity::StaticEntity() : Entity()
{
	
}

Objects::StaticEntity::StaticEntity(const StaticEntity & other) : Entity(other)
{

}

Objects::StaticEntity::StaticEntity(const Entity & other) : Entity(other)
{

}

Objects::StaticEntity::~StaticEntity()
{

}

void Objects::StaticEntity::CreateBoundingBox()
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
	m_boundingBox.SetMinBounds(glm::vec3(minX, minY, minZ));
	m_boundingBox.SetMaxBounds(glm::vec3(maxX, maxY, maxZ));

}

Collision::AABB Objects::StaticEntity::GetBoundingBox()
{
	return m_boundingBox;
}