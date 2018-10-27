#include "AI.h"

typedef enum {
	LookupPath = 1,
	FollowPath = 2
}State;

Objects::AI::AI()
{

}

Objects::AI::~AI()
{

}

glm::vec3 Objects::AI::MoveToWaypoint(glm::vec3 currentPosition, glm::vec3 waypoint, float deltaTime, float speed)
{
	glm::vec3 directionVector = waypoint - currentPosition;
	directionVector = glm::normalize(directionVector);
	currentPosition += directionVector * speed;
	return currentPosition;
}

float Objects::AI::GetAIPositionX()
{
	return aiPositionX;
}

float Objects::AI::GetAIPositionY()
{
	return aiPositionY;
}

void Objects::AI::Update()
{
	switch (currentState) {
		case LookupPath:
		{

		}
		case FollowPath:
		{

		}
		default:
		{
			
		}
	}
}
