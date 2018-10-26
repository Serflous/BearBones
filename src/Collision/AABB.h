#pragma once

#include <GLM/vec3.hpp>

#include "BoundingVolume.h"
#include "BoundingSphere.h"

namespace Collision
{
	class BoundingSphere;
	class AABB : public BoundingVolume
	{
	public:
		AABB();
		AABB(const AABB & other);
		~AABB();

		void SetMinBounds(glm::vec3 minBounds);
		void SetMaxBounds(glm::vec3 maxBounds);
		glm::vec3 GetMinBounds();
		glm::vec3 GetMaxBounds();

		virtual bool IsCollidingWith(BoundingVolume & other);
		virtual bool IsCollidingWith(AABB & other);
		virtual bool IsCollidingWith(BoundingSphere & other);

	private:
		glm::vec3 m_minBounds;
		glm::vec3 m_maxBounds;
	};

}