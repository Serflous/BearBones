#pragma once

#include <GLM/vec3.hpp>
#include <GLM/gtc/quaternion.hpp>

namespace Collision
{

	class OBB
	{
	public:
		OBB();
		OBB(const OBB & other);
		~OBB();

	private:
		glm::vec3 m_minBounds;
		glm::vec3 m_maxBounds;
		glm::vec3 m_centerPoint;
		glm::quat m_rotation;
	};

}