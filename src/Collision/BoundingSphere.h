#pragma once

#include <GLM/vec3.hpp>

#include "BoundingVolume.h"
#include "AABB.h"

namespace Collision
{

	class AABB;
	class BoundingSphere : public BoundingVolume
	{
	public:
		BoundingSphere();
		BoundingSphere(const BoundingSphere & other);
		~BoundingSphere();

		void SetPosition(glm::vec3 position);
		void SetRadius(double radius);
		glm::vec3 GetPosition();
		double GetRadius();

		virtual bool IsCollidingWith(BoundingVolume & other);
		virtual bool IsCollidingWith(BoundingSphere & sphere);
		virtual bool IsCollidingWith(AABB & box);

	private:
		glm::vec3 m_position;
		double m_radius;
	};

}
