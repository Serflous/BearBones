#pragma once

namespace Collision
{
	/**
	 * An Bounding Box's bounding volume.
	 * @author Mathew Causby
	 * @version 0.1
	 */
	class BoundingVolume
	{
		/**
		 * Checks a Bounding Box's bounding volume is colliding with another Bounding Box's bounding volume.
		 * @param[out] Pointer to the other Bounding Box's bounding volume.
		 * @return False if not colliding with another Bounding Box's bounding volume.
		 */
		virtual bool IsCollidingWith(BoundingVolume & other) = 0;
	};

}