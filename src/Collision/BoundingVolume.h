#pragma once

namespace Collision
{
	class BoundingVolume
	{
		virtual bool IsCollidingWith(BoundingVolume & other) = 0;
	};

}