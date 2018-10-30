#define _USE_MATH_DEFINES

#include "AIEntity.h"
//#include "GLM/glm.hpp"

Objects::AIEntity::AIEntity() : Entity()
{

}

Objects::AIEntity::~AIEntity()
{

}

// Set the destination for the AI to move to
void Objects::AIEntity::SetDestination(glm::vec3 destination)
{
	m_destination = destination;
}

// Move the AI towards its destination based on its current speed
bool Objects::AIEntity::IncrementMovement(float deltaTime)
{
	glm::vec3 currentPosition = GetPosition();
	glm::vec3 directionVector = m_destination - currentPosition;

	if (glm::length(directionVector) == 0)
	{
		return true;
	}

	glm::vec3 movementVector = glm::normalize(directionVector) * m_movementSpeed * ((float)deltaTime / 1000);
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

void Objects::AIEntity::ChangeEmotionalState(glm::vec2 change) {
	//do something here to change vector
	m_emotionalState += change;
	if (m_emotionalState.x > 4)
	{
		m_emotionalState.x = 4;
	}
	else if (m_emotionalState.x < -4)
	{
		m_emotionalState.x = -4;
	}
	if (m_emotionalState.y > 4)
	{
		m_emotionalState.y = 4;
	}
	else if (m_emotionalState.y < -4)
	{
		m_emotionalState.y = -4;
	}
}

std::string Objects::AIEntity::GetEmotionalStateAsString() 
{
	//get wheel degrees and emotional intensity
	float intensity = glm::length(m_emotionalState);
	float degree = glm::atan(m_emotionalState.y, m_emotionalState.x);

	if (intensity > 4) {
		intensity = 4;
	}

	float pi8 = M_PI / 8;

	if (degree < pi8 * 5 && degree >= pi8 * 3) {
		// Joy
		if (intensity < 1) {
			return "Neutral";
		}
		else if (intensity < 2) {
			return "Serenity";
		}
		else if (intensity < 3) {
			return "Joy";
		}
		else {
			return "Ecstasy";
		}
	}
	else if (degree < pi8 * 3 && degree >= pi8) {
		// Trust
		if (intensity < 1) {
			return "Neutral";
		}
		else if (intensity < 2) {
			return "Acceptance";
		}
		else if (intensity < 3) {
			return "Trust";
		}
		else {
			return "Admiration";
		}
	}
	else if (degree < pi8 && degree >= -pi8) {

		// Fear
		if (intensity < 1) {
			return "Neutral";
		}
		else if (intensity < 2) {
			return "Apprehension";
		}
		else if (intensity < 3) {
			return "Fear";
		}
		else {
			return "Terror";
		}
	}
	else if (degree < -pi8 && degree >= -pi8 * 3) {
		// Surprise
		if (intensity < 1) {
			return "Neutral";
		}
		else if (intensity < 2) {
			return "Distraction";
		}
		else if (intensity < 3) {
			return "Surprise";
		}
		else {
			return "Amazement";
		}
	}
	else if (degree < -pi8 * 3 && degree >= -pi8 * 5) {
		// Sadness
		if (intensity < 1) {
			return "Neutral";
		}
		else if (intensity < 2) {
			return "Pensiveness";
		}
		else if (intensity < 3) {
			return "Sadness";
		}
		else {
			return "Grief";
		}
	}
	else if (degree < -pi8 * 5 && degree >= -pi8 * 7) {
		// Disgust
		if (intensity < 1) {
			return "Neutral";
		}
		else if (intensity < 2) {
			return "Boredom";
		}
		else if (intensity < 3) {
			return "Disgust";
		}
		else {
			return "Loathing";
		}
	}
	else if ((degree < pi8 * 9 && degree >= pi8 * 7) || degree < -pi8 * 7 && degree >= -pi8 * 9) {
		// Anger
		if (intensity < 1) {
			return "Neutral";
		}
		else if (intensity < 2) {
			return "Annoyance";
		}
		else if (intensity < 3) {
			return "Anger";
		}
		else {
			return "Rage";
		}
	}
	else if (degree < pi8 * 7 && degree >= pi8 * 5) {
		// Anticipation
		if (intensity < 1) {
			return "Neutral";
		}
		else if (intensity < 2) {
			return "Interest";
		}
		else if (intensity < 3) {
			return "Anticipation";
		}
		else {
			return "Vigilance";
		}
	}
}

float Objects::AIEntity::GetWaitTime() 
{
	return m_waitTime;
}

void Objects::AIEntity::CreateBoundingBox(Util::BB_BoundingVolume type)
{

}

void Objects::AIEntity::UpdateBoundingBox()
{

}