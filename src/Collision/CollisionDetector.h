#include <GLM/vec3.hpp>
#include <GLM/gtc/quaternion.hpp>
#include "AABB.h"
#include "OBB.h"

namespace Collision
{

	/**
	 * An Oriented Bounding Box.
	 * @author Mathew Causby
	 * @version 0.1
	 * @TODO Make Sure in TestOBBOBB that t = glm::vec3(glm::dot(t, aAxis[0]), glm::dot(t, aAxis[2]), glm::dot(t, aAxis[2])) is meant to be x, z, z axes
	 */
	class CollisionDetector
	{
	public:
		CollisionDetector();
		bool TestOBBOBB(OBB &a, OBB&b);
	private:

	};

}
