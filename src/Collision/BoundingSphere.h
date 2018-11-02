#pragma once

#include <GLM/vec3.hpp>

#include "BoundingVolume.h"
#include "AABB.h"

namespace Collision
{

	class AABB;
	/**
	 * An Bounding Sphere.
	 * @author
	 * @version 0.1
	 */
	class BoundingSphere : public BoundingVolume
	{
	public:
		BoundingSphere();
		BoundingSphere(const BoundingSphere & other);
		~BoundingSphere();

		/**
		 * Sets the position of the Bounding Sphere.
		 * @param[in] position The position to set the Bounding Sphere to.
		 */
		void SetPosition(glm::vec3 position);

		/**
		 * Sets the radius of the Bounding Sphere.
		 * @param[in] radius The radius to set for the Bounding Sphere.
		 */
		void SetRadius(double radius);

		/**
		 * Gets the position of the Bounding Sphere.
		 * @return The position of the Bounding Sphere.
		 */
		glm::vec3 GetPosition();

		/**
		 * Gets the radius of the Bounding Sphere.
		 * @return The radius of the Bounding Sphere.
		 */
		double GetRadius();

		/**
		 * Checks if the Bounding Sphere is colliding with a Bounding Box's bounding volume.
		 * @param[out] other Pointer to the Bounding Box's bounding volume.
		 * @return False if not colliding with a Bounding Box's bounding volume.
		 */
		virtual bool IsCollidingWith(BoundingVolume & other);

		/**
		 * Checks if the Bounding Sphere is colliding with another Bounding Sphere.
		 * @param[out] other Pointer to the other Bounding Sphere.
		 * @return False if not colliding with a Bounding Sphere. Otherwise return true.
		 */
		virtual bool IsCollidingWith(BoundingSphere & sphere);

		/**
		 * Checks if the Bounding Sphere is colliding with an Axis-Aligned Bounding Box.
		 * @param[out] other Pointer to the Axis-Aligned Bounding Box.
		 * @return False if not colliding with an Axis-Aligned Bounding Box. Otherwise return true.
		 */
		virtual bool IsCollidingWith(AABB & box);

	private:
		glm::vec3 m_position;
		double m_radius;
	};

}
