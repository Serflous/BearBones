#pragma once
#include <vector>
#include <memory>
#include "GLM/glm.hpp"

namespace Objects
{
		/**
		 * A waypoint definition for a location plus a series of other connections
		 * @author Jonathan Sands
		 * @version 0.1
		 */
	class Waypoint
	{
	public:
		Waypoint(glm::vec3 position);
		~Waypoint();

		void SetParent(std::shared_ptr<Objects::Waypoint> parent);
		void Objects::Waypoint::AddConnectedWaypoint(std::shared_ptr<Objects::Waypoint> waypoint);
		std::shared_ptr<Objects::Waypoint> Objects::Waypoint::GetNextWaypoint();
		glm::vec3 Objects::Waypoint::GetPosition();

	private:
		glm::vec3 m_position;
		std::shared_ptr<Objects::Waypoint> m_parent;
		std::shared_ptr<std::vector<std::shared_ptr<Objects::Waypoint>>> m_connectedWaypoints;
	};

}