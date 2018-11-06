#pragma once

#include <GLM/vec3.hpp>

#include "BoundingVolume.h"
#include "BoundingSphere.h"

namespace Collision
{
	class BoundingSphere;
		/**
		 * An Axis-Aligned Bounding Box.
		 * @author Mathew Causby
		 * @version 0.1
		 */
	class AABB : public BoundingVolume
	{
	public:
		AABB();
		AABB(const AABB & other);
		~AABB();

			/**
			 * Sets the minimum values for the Bounding Box.
			 * @param[in] minBounds The minimum values to set for the Bounding Box.
			 */
		void SetMinBounds(glm::vec3 minBounds);

			/**
			 * Sets the maximum values for the Bounding Box.
			 * @param[in] maxBounds The maximum values to set for the Bounding Box.
			 */
		void SetMaxBounds(glm::vec3 maxBounds);

			/**
			 * Gets the minimum values for the Bounding Box.
			 * @return The minimum values for the Bounding Box.
			 */
		glm::vec3 GetMinBounds();

			/**
			 * Gets the maximum values for the Bounding Box.
			 * @return The maximum values for the Bounding Box.
			 */
		glm::vec3 GetMaxBounds();

			/**
			 * Default collision handler if the bounding volume is unknown.
			 * @param[out] other Pointer to the bounding volume.
			 * @return False if not colliding with a bounding volume.
			 */
		virtual bool IsCollidingWith(BoundingVolume & other);

			/**
			 * Checks if the Axis-Aligned Bounding Box is colliding with another Axis-Aligned Bounding Box.
			 * @param[out] other Pointer to the other Axis-Aligned Bounding Box.
			 * @return False if not colliding with an Axis-Aligned Bounding Box. Otherwise return true.
			 */
		virtual bool IsCollidingWith(AABB & other);
			/**
			 * Checks if the Axis-Aligned Bounding Box is colliding with a Bounding Sphere.
			 * @param[out] other Pointer to the Bounding Sphere.
			 * @return False if not colliding with a Bounding Sphere. Otherwise return true.
			 */
		virtual bool IsCollidingWith(BoundingSphere & other);

	private:
		glm::vec3 m_minBounds;
		glm::vec3 m_maxBounds;
	};

}