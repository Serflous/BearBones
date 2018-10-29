#pragma once

#include <vector>
#include <memory>
#include "GLM/glm.hpp"

namespace Objects
{
	int const HEIGHT = 39;//adjust to suit your map size 39
	int const WIDTH = 39; //adjust to suit your map size 39

	struct Waypoint
	{
		glm::vec3 Position;
		bool IsDisabled;

	};

	class AIWaypoints
	{
	public:
		AIWaypoints();
		~AIWaypoints();
		void SetWaypoint();
		std::vector<std::vector<Objects::Waypoint>> GetWaypoint();//add this function to get access to your waypoints outside of this class

	private:
		std::vector<std::vector<Objects::Waypoint>> m_waypoints;
	};
}
