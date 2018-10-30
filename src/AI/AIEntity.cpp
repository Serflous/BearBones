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
	// Change the vector to reflect new emotional state
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
	// Get wheel degrees and emotional intensity
	float intensity = glm::length(m_emotionalState);
	float degree = glm::atan(m_emotionalState.y, m_emotionalState.x);

	if (intensity > 4) {
		intensity = 4;
	}

	// Value of Pi divided by 8
	float pi8 = M_PI / 8;

	// Joy Emotion
	if (degree < pi8 * 5 && degree >= pi8 * 3) {
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
	// Trust Emotion
	else if (degree < pi8 * 3 && degree >= pi8) {
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
	// Fear Emotion
	else if (degree < pi8 && degree >= -pi8) {
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
	// Surprise Emotion
	else if (degree < -pi8 && degree >= -pi8 * 3) {
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
	// Sadness Emotion
	else if (degree < -pi8 * 3 && degree >= -pi8 * 5) {
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
	// Disgust Emotion
	else if (degree < -pi8 * 5 && degree >= -pi8 * 7) {
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
	// Anger Emotion
	else if ((degree < pi8 * 9 && degree >= pi8 * 7) || degree < -pi8 * 7 && degree >= -pi8 * 9) {
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
	// Anticipation Emotion
	else if (degree < pi8 * 7 && degree >= pi8 * 5) {
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

void Objects::AIEntity::CreateBoundingBox(Util::BB_BoundingVolume volume)
{
	m_volumeType = volume;
	if (volume == Util::BB_BV_AABB)
	{
		UpdateBoundingBox();
	}
	else if (volume == Util::BB_BV_OBB)
	{
		float minX, minY, minZ, maxX, maxY, maxZ;
		minX = minY = minZ = std::numeric_limits<float>::max();
		maxX = maxY = maxZ = std::numeric_limits<float>::min();
		std::vector<glm::vec3>::iterator iter;
		std::vector<glm::vec3> verts = GetModel()->GetVerticies();
		glm::vec3 position = GetPosition();
		glm::mat4x4 t = glm::translate(glm::mat4x4(1.0f), position);
		glm::mat4x4 r = glm::rotate(glm::mat4x4(1.0f), GetRotation().x, glm::vec3(1, 0, 0));
		r = glm::rotate(r, GetRotation().y, glm::vec3(0, 1, 0));
		r = glm::rotate(r, GetRotation().z, glm::vec3(0, 0, 1));
		glm::mat4x4 s = glm::scale(glm::mat4x4(1.0f), GetScale());

		for (iter = verts.begin(); iter != verts.end(); iter++)
		{
			glm::vec3 initVert = (*iter);
			glm::vec4 vert = glm::vec4(initVert.x, initVert.y, initVert.z, 1.0f);
			vert = s * vert;
			if (vert.x < minX)
				minX = vert.x;
			if (vert.y < minY)
				minY = vert.y;
			if (vert.z < minZ)
				minZ = vert.z;
			if (vert.x > maxX)
				maxX = vert.x;
			if (vert.y > maxY)
				maxY = vert.y;
			if (vert.z > maxZ)
				maxZ = vert.z;
		}
		//glm::vec3 centerPoint = GetPosition();
		glm::vec3 centerPoint = glm::vec3
		(
			(minX + maxX) / 2.0,
			(minY + maxY) / 2.0,
			(minZ + maxZ) / 2.0
		);
		centerPoint.x += t[3][0];
		centerPoint.y += t[3][1];
		centerPoint.z += t[3][2];
		glm::mat4x4 rotationMatrix = r;
		/*glm::vec3 halfWidths = glm::vec3
		(
		glm::max(glm::abs(centerPoint.x - minX), glm::abs(centerPoint.x - maxX)),
		glm::max(glm::abs(centerPoint.y - minY), glm::abs(centerPoint.y - maxY)),
		glm::max(glm::abs(centerPoint.z - minZ), glm::abs(centerPoint.z - maxZ))
		);*/
		glm::vec3 halfWidths = glm::vec3
		(
			(glm::abs(minX) + glm::abs(maxX)) / 2.0,
			(glm::abs(minY) + glm::abs(maxY)) / 2.0,
			(glm::abs(minZ) + glm::abs(maxZ)) / 2.0
		);
		m_boundingVolume = std::make_shared<Collision::OBB>();
		std::dynamic_pointer_cast<Collision::OBB>(m_boundingVolume)->SetCenterPoint(centerPoint);
		std::dynamic_pointer_cast<Collision::OBB>(m_boundingVolume)->SetRotation(rotationMatrix);
		std::dynamic_pointer_cast<Collision::OBB>(m_boundingVolume)->SetHalfwidth(halfWidths);
	}
}

void Objects::AIEntity::UpdateBoundingBox()
{
	if (m_volumeType == Util::BB_BV_AABB)
	{
		float minX, minY, minZ, maxX, maxY, maxZ;
		minX = minY = minZ = std::numeric_limits<float>::max();
		maxX = maxY = maxZ = std::numeric_limits<float>::min();
		std::vector<glm::vec3>::iterator iter;
		std::vector<glm::vec3> verts = GetModel()->GetVerticies();
		glm::mat4x4 t = glm::translate(glm::mat4x4(1.0f), GetPosition());
		glm::mat4x4 r = glm::rotate(glm::mat4x4(1.0f), GetRotation().x, glm::vec3(1, 0, 0));
		r = glm::rotate(r, GetRotation().y, glm::vec3(0, 1, 0));
		r = glm::rotate(r, GetRotation().z, glm::vec3(0, 0, 1));
		glm::mat4x4 s = glm::scale(glm::mat4x4(1.0f), GetScale());

		for (iter = verts.begin(); iter != verts.end(); iter++)
		{
			glm::vec3 initVert = (*iter);
			glm::vec4 vert = glm::vec4(initVert.x, initVert.y, initVert.z, 1.0f);
			vert = t * r * s * vert;
			if (vert.x < minX)
				minX = vert.x;
			if (vert.y < minY)
				minY = vert.y;
			if (vert.z < minZ)
				minZ = vert.z;
			if (vert.x > maxX)
				maxX = vert.x;
			if (vert.y > maxY)
				maxY = vert.y;
			if (vert.z > maxZ)
				maxZ = vert.z;
		}

		m_boundingVolume = std::make_shared<Collision::AABB>();
		std::dynamic_pointer_cast<Collision::AABB>(m_boundingVolume)->SetMinBounds(glm::vec3(minX, minY, minZ));
		std::dynamic_pointer_cast<Collision::AABB>(m_boundingVolume)->SetMaxBounds(glm::vec3(maxX, maxY, maxZ));
	}
	else if (m_volumeType == Util::BB_BV_OBB)
	{
		glm::vec3 centerPoint = GetPosition();
		std::dynamic_pointer_cast<Collision::OBB>(m_boundingVolume)->SetCenterPoint(centerPoint);
	}
}