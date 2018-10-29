#pragma once

#include <vector>
#include <GLM/glm.hpp>

#include "AIWaypoints.h"
#include "Rendering/Renderer.h"
#include "World.h"

namespace Objects
{
	/**
	 * The AI object contains all functionality for the AI.
	 * @author Jonathan Sands
	 * @version 0.1
	 */
	class AI
	{
	public:
		AI();
		~AI();

		/**
		 * Updates the current state of the AI.
		 */
		void Update();

		/**
		 * Handles the AI's movement from it's current location to its destination.
		 * @param[in] currentPosition The current location of the AI.
		 * @param[in] waypoint The location of the waypoint to move to.
		 * @param[in] deltaTime Used to simulate time progression.
		 * @param[in] speed The speed at which the AI travels between locations.
		 */
		glm::vec3 Objects::AI::MoveToWaypoint(glm::vec3 currentPosition, glm::vec3 waypoint, float deltaTime, float speed);

		/**
		 * Gets the X coordinate of the AI's current position.
		 * @return AI's X coordinate.
		 */
		float GetAIPositionX();

		/**
		 * Gets the Y coordinate of the AI's current position.
		 * @return AI's Y coordinate.
		 */
		float GetAIPositionY();

	private:
		typedef enum State;
		int currentState;
		AIWaypoints *m_gameObject;
		glm::vec3 nextPosition;
		glm::vec3 m_speed;
		float aiPositionX = 0.0;
		float aiPositionY = 0.0;
	};
}