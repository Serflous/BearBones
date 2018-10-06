#pragma once

#include <GLM/vec3.hpp>
#include <GLM/gtc/quaternion.hpp>
#include "AABB.h"

namespace Collision
{

		/**
		 * An Oriented Bounding Box.
		 * @author Mathew Causby
		 * @version 0.1
		 */
	class OBB
	{
	public:
		OBB();
		OBB(const OBB & other);
		OBB(AABB & other);
		~OBB();
		glm::vec3 GetAxesX();
		glm::vec3 GetAxesY();
		glm::vec3 GetAxesZ();
		glm::vec3 * GetAxes();
		glm::vec3 GetCenterPoint();
		glm::vec3 GetHalfSize();


	private:
		glm::vec3 m_minBounds;
		glm::vec3 m_maxBounds;
		glm::vec3 m_centerPoint;
		glm::vec3 m_halfSize;
		glm::vec3 m_axes[3];
		glm::quat m_rotation;

		glm::vec3 HalfSize(AABB & other);
		glm::vec3 Size() const;
	};

}