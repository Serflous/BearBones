#include "Waypoint.h"
#include "GLM/glm.hpp"

Objects::Waypoint::Waypoint(glm::vec3 position)
{
	m_position = position;
	m_connectedWaypoints = std::make_shared<std::vector<std::shared_ptr<Objects::Waypoint>>>();
}

Objects::Waypoint::~Waypoint()
{

}

void Objects::Waypoint::SetParent(std::shared_ptr<Objects::Waypoint> parent)
{
	m_parent = parent;
}

void Objects::Waypoint::AddConnectedWaypoint(std::shared_ptr<Objects::Waypoint> waypoint)
{
	m_connectedWaypoints->push_back(waypoint);
	waypoint->SetParent(std::shared_ptr<Objects::Waypoint>(this));
}

glm::vec3 Objects::Waypoint::GetPosition() {
	return m_position;
}

std::shared_ptr<Objects::Waypoint> Objects::Waypoint::GetNextWaypoint()
{
	int count = m_connectedWaypoints->size();
	if (m_parent != NULL) {
		count++;
	}

	int randomNumber = rand() % count;

	if (randomNumber > m_connectedWaypoints->size() - 1) 
	{
		return m_parent;
	}
	else {
		return m_connectedWaypoints->at(randomNumber);
	}
}