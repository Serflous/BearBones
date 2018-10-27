#include "AIEntity.h"
#include "GLM/glm.hpp"

Objects::AIEntity::AIEntity() : Entity()
{
	
}

Objects::AIEntity::~AIEntity()
{

}

// Set the destination for the AI to move to
void Objects::AIEntity::SetDestination(glm::vec3 dest)
{
	destination = dest;
}

// Move the AI towards its destination based on its current speed
bool Objects::AIEntity::IncrementMovement(float deltaTime)
{
	glm::vec3 currentPosition = GetPosition();
	glm::vec3 directionVector = destination - currentPosition;
	glm::vec3 movementVector = glm::normalize(directionVector) * m_movementSpeed * deltaTime;
	currentPosition += movementVector;
	//SetPosition(currentPosition);

	// Return true if we have reached the destination. 
	if (glm::length(movementVector) >= glm::length(directionVector))
	{
		return true;
	}
	else
	{
		SetPosition(currentPosition);
		return false;
	}
}

void Objects::AIEntity::CreateBoundingBox()
{
	// Don't draw a bounding box for now
}