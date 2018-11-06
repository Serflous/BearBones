#pragma once

#include <GLM/vec3.hpp>
#include <GLM/mat3x3.hpp>

#include "BoundingVolume.h"

namespace Collision
{
		/**
		 * An Oriented Bounding Box.
		 * @author Mathew Causby
		 * @version 0.1
		 */
	class OBB : public BoundingVolume
	{
	public:
		OBB();
		OBB(const OBB & other);
		~OBB();

			/**
			 * Sets the center point of the Oriented Bounding Box.
			 * @param[in] point The point to set the Oriented Bounding Box's center to.
			 */
		void SetCenterPoint(glm::vec3 point);

			/**
			 * Sets the rotation of the Oriented Bounding Box.
			 * @param[in] rotation The rotation to apply to the Oriented Bounding Box.
			 */
		void SetRotation(glm::mat3x3 rotation);

			/**
			 * Sets the half-width of the Oriented Bounding Box.
			 * @param[in] halfwidth The half-width to apply to the Oriented Bounding Box.
			 */
		void SetHalfwidth(glm::vec3 halfwidth);

			/**
			 * Gets the center point of the Oriented Bounding Box.
			 * @return The center point of the Oriented Bounding Box's.
			 */
		glm::vec3 GetCenterPoint();

			/**
			 * Gets the rotation applied the Oriented Bounding Box.
			 * @return The rotation applied to the Oriented Bounding Box.
			 */
		glm::mat3x3 GetRotation();

			/**
			 * Gets the half-width of the Oriented Bounding Box.
			 * @return The half-width applied to the Oriented Bounding Box.
			 */
		glm::vec3 GetHalfWidth();

			/**
			* Default collision handler if the bounding volume is unknown.
			* @param[out] other Pointer to the bounding volume.
			* @return False if not colliding with a bounding volume.
			*/
		virtual bool IsCollidingWith(BoundingVolume & other);

			/**
			 * Checks if the Oriented Bounding Box is colliding with another Oriented Bounding Box.
			 * @param[out] other Pointer to the other Oriented Bounding Box.
			 * @return False if not colliding with another Oriented Bounding Box. Otherwise return true.
			 * @note Code taken from Real Time Collision Detection, Christer Ericson
			 */
		virtual bool IsCollidingWith(OBB & other);

	private:
		glm::vec3 m_centerPoint;
		glm::mat3x3 m_rotationMatrix;
		glm::vec3 m_halfWidths;
	};

}