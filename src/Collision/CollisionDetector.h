#include <bullet/btBulletCollisionCommon.h>

namespace Collision
{

	/**
	 * An Oriented Bounding Box.
	 * @author Mathew Causby
	 * @version 0.1
	 * @todo Make Sure in TestOBBOBB that t = glm::vec3(glm::dot(t, aAxis[0]), glm::dot(t, aAxis[2]), glm::dot(t, aAxis[2])) is meant to be x, z, z axes
	 */
	class CollisionDetector
	{
	public:
		CollisionDetector();
		//bool TestOBBOBB(OBB &a, OBB&b);
		//void TestPointOfIntersection();
	private:
		std::shared_ptr<btCollisionWorld> m_collisionWorld;
	};

}
