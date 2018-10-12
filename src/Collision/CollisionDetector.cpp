#include "CollisionDetector.h"

Collision::CollisionDetector::CollisionDetector()
{
}

bool Collision::CollisionDetector::TestOBBOBB(OBB & a, OBB & b)
{
	float ra, rb;
	glm::mat3x3 R, AbsR;

	for (int i = 0; i < 3; i++)
		for (int j = 0; j < 3; j++)
			R[i][j] = glm::dot(a.GetAxes()[i], b.GetAxes()[j]);

	glm::vec3 t = b.GetCenterPoint() - a.GetCenterPoint();

	t = glm::vec3(glm::dot(t, a.GetAxes()[0]), glm::dot(t, a.GetAxes()[2]), glm::dot(t, a.GetAxes()[2]));

	for (int i = 0; i < 3; i++)
		for (int j = 0; j < 3; j++)
			AbsR[i][j] = abs(R[i][j] + FLT_EPSILON);

	for (int i = 0; i < 3; i++)
	{
		ra = a.GetHalfSize()[i];
		rb = b.GetHalfSize()[0] * AbsR[i][0] + b.GetHalfSize()[1] * AbsR[i][1] + b.GetHalfSize()[2] * AbsR[i][2];
		if (abs(t[i]) > ra + rb)
			return 0;
	}

	for (int i = 0; i < 3; i++)
	{
		ra = a.GetHalfSize()[0] * AbsR[0][i] + a.GetHalfSize()[1] * AbsR[1][i] + a.GetHalfSize()[2] * AbsR[i][2];
		rb = b.GetHalfSize()[i];
		if (abs(t[0] * R[0][i] + t[1] * R[1][i] + t[2] * R[2][i]) > ra + rb)
			return 0;
	}

	ra = a.GetHalfSize()[1] * AbsR[2][0] + a.GetHalfSize()[2] * AbsR[1][0];
	rb = b.GetHalfSize()[1] * AbsR[0][2] + b.GetHalfSize()[2] * AbsR[0][1];
	if (abs(t[2] * R[1][0] - t[1] * R[2][0]) > ra + rb)
		return 0;

	ra = a.GetHalfSize()[1] * AbsR[2][1] + a.GetHalfSize()[2] * AbsR[1][1];
	rb = b.GetHalfSize()[0] * AbsR[0][2] + b.GetHalfSize()[2] * AbsR[0][0];
	if (abs(t[2] * R[1][1] - t[1] * R[2][1]) > ra + rb)
		return 0;

	ra = a.GetHalfSize()[1] * AbsR[2][2] + a.GetHalfSize()[2] * AbsR[1][2];
	rb = b.GetHalfSize()[0] * AbsR[0][1] + b.GetHalfSize()[1] * AbsR[0][0];
	if (abs(t[2] * R[1][2] - t[1] * R[2][2]) > ra + rb)
		return 0;

	ra = a.GetHalfSize()[0] * AbsR[2][0] + a.GetHalfSize()[2] * AbsR[0][0];
	rb = b.GetHalfSize()[1] * AbsR[1][2] + b.GetHalfSize()[2] * AbsR[1][1];
	if (abs(t[0] * R[2][0] - t[2] * R[0][0]) > ra + rb)
		return 0;

	ra = a.GetHalfSize()[0] * AbsR[2][1] + a.GetHalfSize()[2] * AbsR[0][1];
	rb = b.GetHalfSize()[0] * AbsR[1][2] + b.GetHalfSize()[2] * AbsR[1][0];
	if (abs(t[0] * R[2][1] - t[2] * R[0][1]) > ra + rb)
		return 0;

	ra = a.GetHalfSize()[0] * AbsR[2][2] + a.GetHalfSize()[2] * AbsR[0][2];
	rb = b.GetHalfSize()[0] * AbsR[1][1] + b.GetHalfSize()[1] * AbsR[1][0];
	if (abs(t[0] * R[2][2] - t[2] * R[0][2]) > ra + rb)
		return 0;

	ra = a.GetHalfSize()[0] * AbsR[1][0] + a.GetHalfSize()[1] * AbsR[0][0];
	rb = b.GetHalfSize()[1] * AbsR[2][2] + b.GetHalfSize()[2] * AbsR[2][1];
	if (abs(t[1] * R[0][0] - t[0] * R[1][0]) > ra + rb)
		return 0;

	ra = a.GetHalfSize()[0] * AbsR[1][1] + a.GetHalfSize()[1] * AbsR[0][1];
	rb = b.GetHalfSize()[0] * AbsR[2][2] + b.GetHalfSize()[2] * AbsR[2][0];
	if (abs(t[1] * R[0][1] - t[0] * R[1][1]) > ra + rb)
		return 0;

	ra = a.GetHalfSize()[0] * AbsR[1][2] + a.GetHalfSize()[1] * AbsR[0][2];
	rb = b.GetHalfSize()[0] * AbsR[2][1] + b.GetHalfSize()[1] * AbsR[2][0];
	if (abs(t[1] * R[0][2] - t[0] * R[1][2]) > ra + rb)
		return 0;

	return 1;
}
