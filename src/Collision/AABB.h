#pragma once

#include <GLM/vec3.hpp>

namespace Collision
{

	class AABB
	{
	public:
		AABB();
		AABB(const AABB & other);
		~AABB();

		void SetMinBounds(glm::vec3 minBounds);
		void SetMinBounds(float x, float y, float z);
		void SetMaxBounds(glm::vec3 maxBounds);
		void SetMaxBounds(float x, float y, float z);

		glm::vec3 GetMinBounds();
		glm::vec3 GetMaxBounds();

	private:
		glm::vec3 m_minBounds;
		glm::vec3 m_maxBounds;
	};

}