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
		
		/**
		 * Sets the parent waypoint of a child waypoint.
		 * @param[in] parent The waypoint to be assigned as the parent.
		 */
		void SetParent(std::shared_ptr<Objects::Waypoint> parent);

		/**
		 * Connects two waypoints to one another to create a path between them.
		 * @param[in] waypoint The waypoint to connect to.
		 */
		void Objects::Waypoint::AddConnectedWaypoint(std::shared_ptr<Objects::Waypoint> waypoint);

		/**
		 * Gets the position of a waypoint.
		 * @return The position of a waypoint.
		 */
		glm::vec3 Objects::Waypoint::GetPosition();

		/**
		 * Gets the next waypoint for the AI to move to.
		 * @return The next waypoint the AI needs to go to.
		 */
		std::shared_ptr<Objects::Waypoint> Objects::Waypoint::GetNextWaypoint();

	private:
		glm::vec3 m_position; // The position of the waypoint.
		std::shared_ptr<Objects::Waypoint> m_parent; // An object representing a parent waypoint.
		std::shared_ptr<std::vector<std::shared_ptr<Objects::Waypoint>>> m_connectedWaypoints; // An vector containing all the waypoints conntected to a given waypoint.
	};

}