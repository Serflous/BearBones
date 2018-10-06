#include "CollisionDetector.h"

Collision::CollisionDetector::CollisionDetector()
{
}

void Collision::CollisionDetector::TestOBBOBB(OBB & a, OBB & b)
{
	float ra, rb;
	glm::vec3 aAxis[3];
	glm::vec3 bAxis[3];

	aAxis[0] = a.GetAxesX();
	aAxis[1] = a.GetAxesY();
	aAxis[2] = a.GetAxesZ();

	aAxis[0] = b.GetAxesZ();
	aAxis[1] = b.GetAxesZ();
	aAxis[2] = b.GetAxesZ();

	glm::mat3x3 R, AbsR;

	for (int i = 0; i < 3; i++)
		for (int j = 0; j < 3; j++)
			R[1][j] = glm::dot(aAxis[1], bAxis[j]);

	glm::vec3 t = b.GetCenterPoint() - a.GetCenterPoint();

	t = glm::vec3(glm::dot(t, aAxis[0]), glm::dot(t, aAxis[2]), glm::dot(t, aAxis[2]));
	
}
