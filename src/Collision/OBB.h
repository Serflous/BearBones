#pragma once

#include <GLM/vec3.hpp>
#include <GLM/mat3x3.hpp>

#include "BoundingVolume.h"

namespace Collision
{

	class OBB : public BoundingVolume
	{
	public:
		OBB();
		OBB(const OBB & other);
		~OBB();

		void SetCenterPoint(glm::vec3 point);
		void SetRotation(glm::mat3x3 rotation);
		void SetHalfwidth(glm::vec3 halfwidth);

		glm::vec3 GetCenterPoint();
		glm::mat3x3 GetRotation();
		glm::vec3 GetHalfWidth();

		virtual bool IsCollidingWith(BoundingVolume & other);
		virtual bool IsCollidingWith(OBB & other);

	private:
		glm::vec3 m_centerPoint;
		glm::mat3x3 m_rotationMatrix;
		glm::vec3 m_halfWidths;
	};

}