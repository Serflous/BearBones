#include "AIWaypoints.h"

Objects::AIWaypoints::AIWaypoints()
{
	SetWaypoint();
}

Objects::AIWaypoints::~AIWaypoints()
{
}

void Objects::AIWaypoints::SetWaypoint()
{
	float waypointDistanceApart = 10; // change this to suit the map scale and how far apart your waypoints need to be.
	for (int n = 0; n < HEIGHT; n++)
	{
		std::vector<Waypoint> temp;
		m_waypoints.push_back(temp);

		for (int m = 0; m < WIDTH; m++)
		{
			Waypoint tempWaypoint;
			tempWaypoint.Position.x = (waypointDistanceApart * n) - 190; //x value
			tempWaypoint.Position.y = 0;
			tempWaypoint.Position.z = (waypointDistanceApart * m) - 170; //z value;
			/*if(Function to check if the point is in any disabled areas == true)
			{
				tempWaypoint.IsDisabled = true;
			}
			else
			{
				tempWaypoint.IsDisabled = false;
			}*/
			m_waypoints[n].push_back(tempWaypoint);

		}
	}
}

std::vector<std::vector<Objects::Waypoint>> Objects::AIWaypoints::GetWaypoint()
{
	return m_waypoints;
}
