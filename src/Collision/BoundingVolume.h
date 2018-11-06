#pragma once

namespace Collision
{
		/**
		 * An abstract class that every boudning volume will inherit from.
		 * @author Mathew Causby
		 * @version 0.1
		 */
	class BoundingVolume
	{
			/**
			 * Pure virtual function that every child will require. Will be the defaulkt check for bounding volumes.
			 * @param[out] Pointer to the other bounding volume.
			 * @return False if not colliding with another bounding volume.
			 */
		virtual bool IsCollidingWith(BoundingVolume & other) = 0;
	};

}